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
    void getAtoms(AtomFunctionMap& m);
    void setOptions(bool doHelp, std::vector<std::string>& argv,
                    std::ostream& out);

private:
    bool activatePlugin;
    ScriptConverter* converter;
};

  } // namespace script
} // namespace dlvhex

#endif // _DLVHEX_SCRIPTPLUGIN_H
