/* -*- C++ -*- */

/**
 * @file   ScriptAtom.h
 * @author Anton Korosec
 * @date   February 2007
 *
 * @brief  script-plugin for DLVHEX
 */

#include <dlvhex/PluginInterface.h>
#include <sys/types.h>
#include <sys/wait.h>


class ScriptAtom : public PluginAtom {

public:
    ScriptAtom();
    void retrieve(const Query& query, Answer& answer) throw (PluginError);
};
