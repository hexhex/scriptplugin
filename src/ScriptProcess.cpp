#include "ScriptProcess.h"

namespace dlvhex {
 namespace script {

	ScriptProcess::ScriptProcess(const std::string &caller) : proc() {
		parent = caller;
		// setup streams
		ipipe = new std::iostream(&proc);
		opipe = new std::iostream(&proc);
	}

	ScriptProcess::~ScriptProcess() {
		proc.close(true);
		delete ipipe;
		delete opipe;
	}

	std::ostream& ScriptProcess::execute(const std::string &c, std::istream& in) throw (PluginError) {

		std::vector<std::string> args;
		args.push_back(c);

		proc.open(args); 
		*ipipe << in.rdbuf(); 
		proc.endoffile(); 

		int status = proc.close();

		if (status == 0) {

			return *opipe;

		} else {
			std::stringstream s;
			s << "Error executing script, called by " << parent << ": ";
			s << opipe;
			s << "(exit status " << status << ") ";
			if (status == 127) {
				s << "(maybe you want to use the --addpath option)";
			}
			
			throw PluginError(s.str());
		}
	}

 }
}
