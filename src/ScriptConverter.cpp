/* -*- C++ -*- */

/**
 * @file   ScriptConverter.cpp
 * @author Anton Korosec
 * @date   February 2007
 *
 * @brief  script-converter for DLVHEX
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "ScriptConverter.h"

#include <climits>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cerrno>

#include <sys/wait.h>

namespace dlvhex {
  namespace script {

ScriptConverter::ScriptConverter() {
    // init
}


void
ScriptConverter::setConverter(const std::vector<std::string>& convScript) {

    // set converter(script), which will be called to convert the input

    this->scriptVector = convScript;
}


void
ScriptConverter::convert(std::istream& i, std::ostream& o) {

    if (scriptVector.size() < 1) {
        throw PluginError("No converter-script given");

        // or maybe just pass the original input to the o-stream...
        // o = i; return;
    }

    // the command, which will be executed, consists of the script
    // and the temporary file (containing the istream i) as argument

    // we can add more than just the first element of scriptVector

    std::string tmpfilename(::tmpnam(NULL));

    const std::string command =
      scriptVector.at(0) + " " + tmpfilename;

    // create two pipes

    int stdoutpipe[2];
    int stderrpipe[2];
    pid_t pid;
    int status;

    if (::pipe(stdoutpipe) < 0) {
        throw PluginError("Error while creating pipe");
    }

    if (::pipe(stderrpipe) < 0) {
        throw PluginError("Error while creating pipe");
    }

    // create a temporary file and save the istream i in it

    std::ofstream file(tmpfilename.c_str());
    std::string s;

    if (!file.is_open()) {
        throw PluginError("Error while creating temp-file");
    }

    while (std::getline(i, s, '\n')) {
        file << s << std::endl;
    }

    // fork process

    switch (pid = ::fork()) {

        case -1:
        {
            ScriptConverter::removeTempFile(tmpfilename);
            throw PluginError("Error while forking process");
            break;
        }

        case 0:
        {
            // ChildProcess: redirect stdout and stderr to the pipes,
            //               close pipe-ends and execute the command

            if (::dup2(stdoutpipe[1], STDOUT_FILENO) < 0) {
                ScriptConverter::removeTempFile(tmpfilename);
                throw PluginError("Error while duplicating pipe-end");
            }

            if (::dup2(stderrpipe[1], STDERR_FILENO) < 0) {
                ScriptConverter::removeTempFile(tmpfilename);
                throw PluginError("Error while duplicating pipe-end");
            }

            if (::close(stdoutpipe[0]) < 0) {
                ScriptConverter::removeTempFile(tmpfilename);
                throw PluginError("Error while closing pipe-end");
            }

            if (::close(stdoutpipe[1]) < 0) {
                ScriptConverter::removeTempFile(tmpfilename);
                throw PluginError("Error while closing pipe-end");
            }

            if (::close(stderrpipe[0]) < 0) {
                ScriptConverter::removeTempFile(tmpfilename);
                throw PluginError("Error while closing pipe-end");
            }

            if (::close(stderrpipe[1]) < 0) {
                ScriptConverter::removeTempFile(tmpfilename);
                throw PluginError("Error while closing pipe-end");
            }

            // the -c flag means: "Pass the string argument to the shell to be
            //                     interpreted as input."

            if (::execlp("/bin/sh", "sh", "-c", command.c_str(), (char *) 0) < 0) {
                ScriptConverter::removeTempFile(tmpfilename);
                throw PluginError("Error while executing command");
            }

            ScriptConverter::removeTempFile(tmpfilename);
            throw PluginError("Error while executing command");
            break;
        }

        default:
        {
            // FatherProcess: close pipe-ends we dont

            if (::close(stdoutpipe[1]) < 0) {
                ScriptConverter::removeTempFile(tmpfilename);
                throw PluginError("Error while closing pipe-end");
            }

            if (::close(stderrpipe[0]) < 0) {
                ScriptConverter::removeTempFile(tmpfilename);
                throw PluginError("Error while closing pipe-end");
            }

            if (::close(stderrpipe[1]) < 0) {
                ScriptConverter::removeTempFile(tmpfilename);
                throw PluginError("Error while closing pipe-end");
            }

            // wait until ChildProcess terminates

            if (::waitpid(pid, &status, 0) < 0) {
                ScriptConverter::removeTempFile(tmpfilename);
                throw PluginError("Error while waiting on child-process");
            }

            // if the ChildProcess exited normally than get result from pipe

            if (WIFEXITED(status)) {
                if (WEXITSTATUS(status) == 0) {

                    // open pipe for reading

                    FILE *reading;
                    char puffer[PIPE_BUF];

                    if ((reading = ::fdopen(stdoutpipe[0], "r")) == (FILE *) NULL) {
                        ScriptConverter::removeTempFile(tmpfilename);
                        throw PluginError("Error while opening pipe for reading");
                    }

                    // read from pipe (line-wise) and pass the result to the ostream o

                    // what we read from the pipe stream is the result, which was
                    // printed to stdout, from the script that we executed in the
                    // ChildProcess

                    // maybe even check if stderrpipe is empty and
                    // handle errors from script

                    while (::fgets(puffer, PIPE_BUF, reading)) {
                        o << puffer << std::endl;
                    }

                    if (::ferror(reading)) {
                        ScriptConverter::removeTempFile(tmpfilename);
                        throw PluginError("Error while reading from pipe");
                    }

                    // close the pipe stream

                    if (::fclose(reading) == EOF) {
                        ScriptConverter::removeTempFile(tmpfilename);
                        throw PluginError("Error while closing pipe-stream");
                    }
                }
            } else {
                ScriptConverter::removeTempFile(tmpfilename);
                std::stringstream s;
                s << "Error executing '/bin/sh -c " << command << "'";
#                 ifdef _GNU_SOURCE
                s << " pwd='" << ::get_current_dir_name() << "'";
#                 endif
                s << " shell returned exit status " << WEXITSTATUS(status);
                if( WEXITSTATUS(status) == 127 )
                  s << " (maybe you want to use the --addpath option)";
                throw PluginError(s.str());
            }

            break;
        }
    }

    ScriptConverter::removeTempFile(tmpfilename);
}


void
ScriptConverter::removeTempFile(const std::string& fname) {
  if( ::remove(fname.c_str()) )
  {
    throw PluginError("Error while deleting temp-file: " + std::string(::strerror(errno)));
  }
}

  } // namespace script
} // namespace dlvhex
