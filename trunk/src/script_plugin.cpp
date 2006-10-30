/* -*- C++ -*- */

/**
 * @file   scriptplugin.cpp
 * @author Anton Korosec
 * @date   October 2006
 * 
 * @brief  script-plugin for DLVHEX
 */


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "dlvhex/PluginInterface.h"
#include <cstdio>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cerrno>
#include <csignal>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>


class ScriptAtom : public PluginAtom
{
public:
    
    ScriptAtom()
    {
        addInputConstant();
        
        setOutputArity(1);
    }
    
    virtual void
    retrieve(const Query& query, Answer& answer) throw (PluginError)
    {
        
        std::string in;
        in = query.getInputTuple()[0].getUnquotedString();
        
        std::vector<Tuple> out;
        
        int stdoutpipe[2];
        int stderrpipe[2];
        
        pid_t process;
        int status;
        
        if (::pipe(stdoutpipe) < 0) {
            throw PluginError("Error while creating pipe");
        }
        
        if (::pipe(stderrpipe) < 0) {
            throw PluginError("Error while creating pipe");
        }
        
        process = ::fork();
        
        switch (process) {
           
            case -1:
            {
                throw PluginError("Error while forking process");
            break;
            }
            
            case 0:
            {
                if (::dup2(stdoutpipe[1],STDOUT_FILENO) < 0) {
                    throw PluginError("Error while duplicating pipe-end");
                }
                
                if (::dup2(stderrpipe[1],STDERR_FILENO) < 0) {
                    throw PluginError("Error while duplicating pipe-end");
                }
                
                if (::close(stdoutpipe[0]) < 0) {
                    throw PluginError("Error while closing pipe-end");
                }
                
                if (::close(stdoutpipe[1]) < 0) {
                    throw PluginError("Error while closing pipe-end");
                }
                
                if (::close(stderrpipe[0]) < 0) {
                    throw PluginError("Error while closing pipe-end");
                }
                
                if (::close(stderrpipe[1]) < 0) {
                    throw PluginError("Error while closing pipe-end");
                }
                
/**             alternative approach (doesnt work) => remove...
                char *cmdArray[100];
                
                int start;
                int end;
                int i;
                
                start = 0;
                end = 0;
                i = 0;
                
                while ((end = in.find(" ", start)) != std::string::npos) {
                    strcpy(cmdArray[i],(in.substr(start, end-start)).c_str());
                    start = end + 1;
                    i++;
                }
                
                if (in.size() > 0) {
                    strcpy(cmdArray[i],(in.substr(start)).c_str());
                }
                
                cmdArray[++i] = (char *)0;
**/             
                
                
/****/          
                std::vector<std::string> cmdVector;
                std::string buf;
                std::stringstream ss(in);
                
                while (ss >> buf) {
                    cmdVector.push_back(buf);
                }
                
                char *cmdArray[cmdVector.size()+1];
                
                int j;
                for (j=0; j<cmdVector.size(); j++) {
                    strcpy(cmdArray[j],cmdVector.at(j).c_str());
                }
                
                cmdArray[++j] = (char *)0;
/****/          
                
                
                if (execvp(cmdArray[0], cmdArray) < 0) {
                    throw PluginError("Error while executing command");
                }
                
                throw PluginError("Error while executing command");
            
            break;
            }
            
            default:
            {
                if (::close(stdoutpipe[1]) < 0) {
                    throw PluginError("Error while closing pipe-end");
                }
                
                if (::close(stderrpipe[1]) < 0) {
                    throw PluginError("Error while closing pipe-end");
                }
                
                if (::waitpid(process,&status,0) < 0) {
                    throw PluginError("Error while waiting on child-process");
                }
               
                // TODO: eventually check if STDERR has data... necessary?
                //       check if script terminated with an error...?
                
                FILE *reading;
                char puffer[PIPE_BUF];
                
                if (!(reading = ::fdopen(stdoutpipe[0],"r"))) {
                    throw PluginError("Error while associating stream with file-descriptor");
                }
                
                while (::fgets(puffer,PIPE_BUF,reading) != NULL) {
                    puffer[strlen(puffer)-1] = '\0';
                   
                    Tuple tuple;
                    // maybe use 'false'-tag, when getting just an INT
                    tuple.push_back(Term(puffer,true));
                    out.push_back(tuple);
                }
                
                if (::ferror(reading)) {
                    throw PluginError("Error while reading from pipe");
                }
                
                if (::fclose(reading) == EOF) {
                    throw PluginError("Error while closing file-descriptor");
                }
                
                answer.addTuples(out);
                
            break;
            }
        }
    }
};


class ScriptPlugin : public PluginInterface
{
public:
    virtual void
    getAtoms(AtomFunctionMap& a)
    {
        a["script"] = new ScriptAtom;
    }
    
    // implement setOptions()-method; if needed...
};


ScriptPlugin theScriptPlugin;

extern "C"
ScriptPlugin*
PLUGINIMPORTFUNCTION()
{
    theScriptPlugin.setVersion(SCRIPTPLUGIN_MAJOR,
                               SCRIPTPLUGIN_MINOR,
                               SCRIPTPLUGIN_MICRO);
    
    return &theScriptPlugin;
}

