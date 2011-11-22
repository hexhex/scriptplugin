#include "dlvhex/ProcessBuf.h"
#include <dlvhex/PluginInterface.h>

#include <string>
#include <iosfwd> 

namespace dlvhex {
 namespace script {

  class ScriptProcess {

	public:
	ScriptProcess(const std::string &caller);
	~ScriptProcess(); 
	std::ostream& execute(const std::string &c, std::istream &in) throw (PluginError);

	private:
	std::string parent;
	ProcessBuf proc;
	std::iostream *ipipe;
	std::iostream *opipe;

  };

 }
}
