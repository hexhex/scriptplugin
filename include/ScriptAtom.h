/* -*- C++ -*- */

/**
 * @file   ScriptAtom.h
 * @author Anton Korosec
 * @date   February 2007
 *
 * @brief  script-plugin for DLVHEX
 */

#if !defined(_DLVHEX_SCRIPTATOM_H)
#define _DLVHEX_SCRIPTATOM_H

#include <dlvhex2/PluginInterface.h>
#include "ScriptProcess.h"

namespace dlvhex {
  namespace script {

class ScriptAtom : public PluginAtom {
public:
	ScriptAtom();
	void retrieve(const Query& query, Answer& answer) throw (PluginError);
};

  } // namespace script
} // namespace dlvhex

#endif // _DLVHEX_SCRIPTATOM_H
