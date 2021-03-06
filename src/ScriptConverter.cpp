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
ScriptConverter::setConverter(const std::string& convScript) {
    // set converter(script), which will be called to convert the input
    this->script = convScript;
}
	  
bool
ScriptConverter::hasConverter() {
	return !this->script.empty();
}


void
ScriptConverter::convert(std::istream& in, std::ostream& out) {

	if (script.empty()) {
		throw PluginError("No converter-script given");

		// or maybe just pass the original input to the o-stream...
		// o = i; return;
	}

	// store in into temp file
  std::string tmpfilename(::tmpnam(NULL));
	std::ofstream file(tmpfilename.c_str());
	std::string s;

	if (!file.is_open())
  {
    std::ostringstream os;
    os << "Error while creating temp-file '" << tmpfilename << "'";
		throw PluginError(os.str());
	}

	while (std::getline(in, s, '\n')) {
		file << s << std::endl;
	}

	// the command, which will be executed, consists of the script
	// and the temporary file (containing the istream i) as argument

	// we can add more than just the first element of scriptVector

	std::string command = script + " " + tmpfilename;

	ScriptProcess cp("ScriptConverter");

	std::vector<std::string> args;
	args.push_back("sh");
	args.push_back("-c");
	args.push_back(command.c_str());

	std::istringstream dummyin;
	std::stringstream &out_temp = cp.execute(args, dummyin);

	out << out_temp.str();

	// remove the temporary file
  if( ::remove(tmpfilename.c_str()) != 0)
  {
    std::ostringstream os;
    os << "Error while deleting temp-file '" <<
      tmpfilename << "':" <<
      std::string(::strerror(errno));
    throw PluginError(os.str());
  }
}

  } // namespace script
} // namespace dlvhex
