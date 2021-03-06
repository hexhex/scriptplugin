/* -*- C++ -*- */

/**
 * @file   ScriptConverter.h
 * @author Anton Korosec
 * @date   February 2007
 *
 * @brief  script-converter for DLVHEX
 */

#if !defined(_DLHVEX_SCRIPTCONVERTER_H)
#define _DLVHEX_SCRIPTCONVERTER_H

#include <dlvhex2/PluginInterface.h>
#include <fstream>

#include "ScriptProcess.h"

namespace dlvhex {
  namespace script {

class ScriptConverter : public PluginConverter {
public:
	ScriptConverter();
    void setConverter(const std::string& convScript);
	bool hasConverter();
    virtual void convert(std::istream& i, std::ostream& o);

private:
    std::string script;
};

  } // namespace script
} // namespace dlvhex

#endif // _DLVHEX_SCRIPTCONVERTER_H
