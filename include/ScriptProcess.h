#include "dlvhex/ProcessBuf.h"
#include <dlvhex/PluginInterface.h>

#include <string>
#include <iosfwd> 
#include <stdio.h>

#ifndef _DLVHEX_SCRIPTPROCESS_H
#define _DLVHEX_SCRIPTPROCESS_H
namespace dlvhex {
 namespace script {

  class ScriptProcess {

	public:
	ScriptProcess(const std::string &caller);
	~ScriptProcess(); 
	std::stringstream& execute(const std::vector<std::string> &args, std::istream &in) throw (PluginError);

	private:
	std::string parent;
	ProcessBuf proc;
	std::iostream *ipipe;
	std::iostream *opipe;
  };

 }
}
#endif
