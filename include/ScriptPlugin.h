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
#include <dlvhex/PluginInterface.h>

namespace dlvhex {
  namespace script {

class ScriptPlugin : public PluginInterface {
public:
    ScriptPlugin();
    ~ScriptPlugin();
    PluginConverter* createConverter();
	std::vector<PluginAtomPtr> createAtoms(ProgramCtx&) const;
    void processOptions(std::list<const char*>& pluginOptions, ProgramCtx& ctx);

private:
    bool activatePlugin;
    std::string addToPath;
    ScriptConverter* converter;
};

  } // namespace script
} // namespace dlvhex

#endif // _DLVHEX_SCRIPTPLUGIN_H
