/* -*- C++ -*- */

/**
 * @file   ScriptPlugin.h
 * @author Anton Korosec
 * @date   February 2007
 *
 * @brief  script-plugin for DLVHEX
 */

#include "ScriptAtom.h"
#include "ScriptConverter.h"
#include <dlvhex/PluginInterface.h>


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

ScriptPlugin theScriptPlugin;
extern "C" ScriptPlugin* PLUGINIMPORTFUNCTION();
