/* -*- C++ -*- */

/**
 * @file   ScriptPlugin.cpp
 * @author Anton Korosec
 * @date   February 2007
 *
 * @brief  script-plugin for DLVHEX
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "ScriptPlugin.h"

#include <cstdlib>


namespace dlvhex {
  namespace script {

	ScriptPlugin::ScriptPlugin()
    		: activatePlugin(0), addToPath(""), converter(new ScriptConverter()) {
    	
    		setNameVersion(PACKAGE_TARNAME, SCRIPTPLUGIN_MAJOR, 
    			SCRIPTPLUGIN_MINOR, SCRIPTPLUGIN_MICRO);
	}


	ScriptPlugin::~ScriptPlugin() {
    		delete converter;
	}


	void
	ScriptPlugin::getAtoms(PluginAtomMap& a) {
  		PluginAtomPtr script(new ScriptAtom);
  		a["script"] = script;
	}


	void
	ScriptPlugin::setOptions(bool doHelp, std::vector<std::string>& argv, std::ostream& out) {

    		if (doHelp) {
        		//      123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-
		        out << "Script-plugin: " << std::endl << std::endl;
		        out << " --convert=SCRIPT Specify script for converting the input" << std::endl;
		        out << " --addpath=PATH   Specify paths to prepend to the shell PATH " 
		        	<< "variable (searchpath for scripts)" << std::endl;
		        return;
    		}

		std::vector<std::string> convScript;
		std::vector<std::vector<std::string>::iterator> found;
		std::string::size_type o;

    		for (std::vector<std::string>::iterator it = argv.begin(); it != argv.end(); ++it) {

        		o = it->find("--convert=");
        		if (o != std::string::npos) {
            		this->activatePlugin = 1;

            		convScript.push_back(it->substr(10));
            		converter->setConverter(convScript);
            		found.push_back(it);
            		continue;
        		}

        		o = it->find("--addpath=");
        		if (o != std::string::npos) {
            		this->addToPath = it->substr(10);
            		found.push_back(it);
            		continue;
        		}
    		}

    		for (std::vector<std::vector<std::string>::iterator>::const_iterator it = found.begin(); 
    				it != found.end(); ++it) {
        		argv.erase(*it);
    		}

    		// immediately set the environment for the whole process,
    		// which is inherited by subprocesses.
    		if( !this->addToPath.empty() ) {
      		// pre(!)pend path to existing PATH
      		std::string path(::getenv("PATH"));
      		if( path.empty() )
        			path = this->addToPath;
      		else 
        			path = this->addToPath + ":" + path;
      		::setenv("PATH", path.c_str(), 1);
    		}
	}


	PluginConverter*
	ScriptPlugin::createConverter() {
    		if (!this->activatePlugin) {
        		return 0;
    		}

    		return converter;
	}


	ScriptPlugin theScriptPlugin;

  } // namespace script
} // namespace dlvhex

//extern "C"
//dlvhex::script::ScriptPlugin*
//PLUGINIMPORTFUNCTION() {
//  dlvhex::script::theScriptPlugin.setPluginName(PACKAGE_TARNAME);
//  dlvhex::script::theScriptPlugin.setVersion(SCRIPTPLUGIN_MAJOR,
//					     SCRIPTPLUGIN_MINOR,
//					     SCRIPTPLUGIN_MICRO);

//  return &dlvhex::script::theScriptPlugin;
//}

extern "C"
void *PLUGINIMPORTFUNCTION() {
	return reinterpret_cast<void*>(& dlvhex::script::theScriptPlugin);
}
