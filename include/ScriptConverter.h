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

#include <dlvhex/PluginInterface.h>
#include <fstream>

namespace dlvhex {
  namespace script {

class ScriptConverter : public PluginConverter {
public:
    ScriptConverter();

    void
    setConverter(const std::vector<std::string>& convScript);

    virtual void
    convert(std::istream& i, std::ostream& o);

private:
    std::vector<std::string> scriptVector;
    void removeTempFile(const std::string& fname);
};

  } // namespace script
} // namespace dlvhex

#endif // _DLVHEX_SCRIPTCONVERTER_H
