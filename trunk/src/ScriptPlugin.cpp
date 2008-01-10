/* -*- C++ -*- */

/**
 * @file   ScriptPlugin.cpp
 * @author Anton Korosec
 * @date   February 2007
 *
 * @brief  script-plugin for DLVHEX
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "ScriptPlugin.h"


namespace dlvhex {
  namespace script {

ScriptPlugin::ScriptPlugin()
    : converter(new ScriptConverter()) {
}


ScriptPlugin::~ScriptPlugin() {
    delete converter;
}


void
ScriptPlugin::getAtoms(AtomFunctionMap& a) {
  boost::shared_ptr<PluginAtom> script(new ScriptAtom);
  a["script"] = script;
}


void
ScriptPlugin::setOptions(bool doHelp, std::vector<std::string>& argv,
                         std::ostream& out) {

    if (doHelp) {
        //      123456789-123456789-123456789-123456789-123456789-123456789-123456789-123456789-
        out << "Script-plugin: " << std::endl << std::endl;
        out << " --convert=SCRIPT Specify script for converting the input" << std::endl;
        return;
    }

    std::vector<std::string> convScript;
    std::vector<std::vector<std::string>::iterator> found;
    std::string::size_type o;

    for (std::vector<std::string>::iterator it = argv.begin();
         it != argv.end(); ++it) {

        o = it->find("--convert=");

        if (o != std::string::npos) {
            this->activatePlugin = 1;

            convScript.push_back(it->substr(10));
            converter->setConverter(convScript);
            found.push_back(it);
        }
    }

    for (std::vector<std::vector<std::string>::iterator>::const_iterator it =
         found.begin(); it != found.end(); ++it) {
        argv.erase(*it);
    }
}


PluginConverter*
ScriptPlugin::createConverter() {
    if (!this->activatePlugin) {
        return 0;
    }

    return converter;
}


ScriptPlugin theScriptPlugin;

  } // namespace script
} // namespace dlvhex

extern "C"
dlvhex::script::ScriptPlugin*
PLUGINIMPORTFUNCTION() {
  dlvhex::script::theScriptPlugin.setVersion(SCRIPTPLUGIN_MAJOR,
					     SCRIPTPLUGIN_MINOR,
					     SCRIPTPLUGIN_MICRO);

  return &dlvhex::script::theScriptPlugin;
}
