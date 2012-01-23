/* -*- C++ -*- */

/**
 * @file   ScriptPlugin.h
 * @author Anton Korosec
 * @date   February 2007
 *
 * @brief  script-plugin for DLVHEX
 */

#if !defined(_DLVHEX_SCRIPTPLUGIN_H)
#define _DLVHEX_SCRIPTPLUGIN_H

#include "ScriptAtom.h"
#include "ScriptConverter.h"
#include <dlvhex2/PluginInterface.h>

namespace dlvhex {
  namespace script {

class ScriptPlugin : public PluginInterface {
public:
    ScriptPlugin();
    ~ScriptPlugin();
    PluginConverterPtr createConverter(ProgramCtx& ctx);
	std::vector<PluginAtomPtr> createAtoms(ProgramCtx&) const;
    void processOptions(std::list<const char*>& pluginOptions, ProgramCtx& ctx);
	void printUsage(std::ostream& o);

private:
    std::string addToPath;
	boost::shared_ptr<ScriptConverter> converter;
};

  } // namespace script
} // namespace dlvhex

#endif // _DLVHEX_SCRIPTPLUGIN_H
