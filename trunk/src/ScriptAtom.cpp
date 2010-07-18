/* -*- C++ -*- */

/**
 * @file   ScriptAtom.cpp
 * @author Anton Korosec
 * @date   February 2007
 *
 * @brief  script-plugin for DLVHEX
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "ScriptAtom.h"

#include <unistd.h>
#include <cstdio>
#include <climits>
#include <cstring>
#include <sstream>
#include <cstdlib>

#include <sys/wait.h>

namespace dlvhex {
  namespace script {

ScriptAtom::ScriptAtom() {
    addInputConstant();
    setOutputArity(1);
}


void
ScriptAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {

    std::string in = query.getInputTuple()[0].getUnquotedString();
    std::vector<Tuple> out;

    // create two pipes and fork process

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

    switch (pid = ::fork()) {

        case -1:
        {
            throw PluginError("Error while forking process");
            break;
        }

        case 0:
        {
            // ChildProcess: redirect stdout and stderr to the pipes,
            //               close pipe-ends and execute the command

            if (::dup2(stdoutpipe[1], STDOUT_FILENO) < 0) {
                throw PluginError("Error while duplicating pipe-end");
            }

            if (::dup2(stderrpipe[1], STDERR_FILENO) < 0) {
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

            // the -c flag means: "Pass the string argument to the shell to be
            //                     interpreted as input."

            if (::execlp("/bin/sh", "sh", "-c", in.c_str(), (char *) 0) < 0) {
                throw PluginError("Error while executing command");
            }

            throw PluginError("Error while executing command");
            break;
        }

        default:
        {
            // FatherProcess: close pipe-ends we dont need

            if (::close(stdoutpipe[1]) < 0) {
                throw PluginError("Error while closing pipe-end");
            }

            if (::close(stderrpipe[0]) < 0) {
                throw PluginError("Error while closing pipe-end");
            }

            if (::close(stderrpipe[1]) < 0) {
                throw PluginError("Error while closing pipe-end");
            }

            // wait until ChildProcess terminates

            if (::waitpid(pid, &status, 0) < 0) {
                throw PluginError("Error waiting for child-process");
            }

            // if the ChildProcess exited normally than get result from pipe

            if (WIFEXITED(status)) {
                if (WEXITSTATUS(status) == 0) {

                    FILE *reading;
                    char puffer[PIPE_BUF];

                    // open pipe for reading and read from it (line-wise)

                    if ((reading = ::fdopen(stdoutpipe[0], "r")) == (FILE *) NULL) {
                        throw PluginError("Error while opening pipe for reading");
                    }

                    bool isInt = true;

                    // what we read from the pipe stream is the result, which was
                    // printed to stdout, from the script that we executed in the
                    // ChildProcess

                    // maybe even check if stderrpipe is empty and
                    // handle errors from script

                    while (::fgets(puffer, PIPE_BUF, reading)) {

                        puffer[::strlen(puffer)-1] = '\0';

                        Tuple tuple;

                        // test if every character is a digit

                        for (int i=0; i<(::strlen(puffer)-1); i++) {
                            if (!::isdigit(puffer[i])) {
                                isInt = false;
                            }
                        }

                        // if there are just digits => 2nd argument of Term() is FALSE
                        //                             (creates a "number term"
                        //                              without quotes)
                        //                     else => 2nd argument is TRUE (creates a
                        //                              "string term" with quotes)

                        if (isInt) {
                            tuple.push_back(Term(puffer, false));
                        } else {
                            tuple.push_back(Term(puffer, true));
                        }

                        // we just create "single tuples"
                        // (each tuple has only one term)

                        out.push_back(tuple);
                    }

                    if (::ferror(reading)) {
                        throw PluginError("Error while reading from pipe");
                    }

                    // close the pipe stream

                    if (::fclose(reading) == EOF) {
                        throw PluginError("Error while closing pipe-stream");
                    }
                }
                else
                {
                  std::stringstream s;
                  s << "Error executing '/bin/sh -c " << in << "'";
#                 ifdef _GNU_SOURCE
                  s << " pwd='" << ::get_current_dir_name() << "'";
#                 endif
                  s << " shell returned exit status " << WEXITSTATUS(status);
                  if( WEXITSTATUS(status) == 127 )
                    s << " (maybe you want to use the --addpath option)";
                  throw PluginError(s.str());
                }
            }

            answer.addTuples(out);

            break;
        }
    }
}

  } // namespace script
} // namespace dlvhex
