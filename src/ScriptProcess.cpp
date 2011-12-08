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

	std::stringstream& ScriptProcess::execute(const std::vector<std::string> &args, 
											std::istream &in) throw (PluginError) {

		proc.open(args); 
		*ipipe << in.rdbuf(); 
		proc.endoffile(); 

		// copy content of opipe->rdbuf() to own streambuf	
		std::streambuf *backup = opipe->rdbuf();
		char ch;
		std::string content;
		do {
			ch = backup->sgetc();
			content.push_back(ch);
		}
		while (backup->snextc() != EOF);
		
		out.str(content);

		int status = proc.close(); // this closes ipipe and opipe

		if (status == 0) {

			return out;

		} else {
			std::stringstream s;
			s << "Error executing script, called by " << parent << ": ";
			s << out;
			s << "(exit status " << status << ") ";
			if (status == 127) {
				s << "(maybe you want to use the --addpath option)";
			}
			
			throw PluginError(s.str());
		}
	}

 }
}
