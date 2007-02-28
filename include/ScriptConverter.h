/* -*- C++ -*- */

/**
 * @file   ScriptConverter.h
 * @author Anton Korosec
 * @date   February 2007
 *
 * @brief  script-converter for DLVHEX
 */

#include <dlvhex/PluginInterface.h>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>

#define TEMP_FILE_NAME ".dlvhex_conv.tmp"


class ScriptConverter : public PluginConverter {

public:
    ScriptConverter();
    void ScriptConverter::setConverter(std::vector<std::string> convScript);
    virtual void ScriptConverter::convert(std::istream& i, std::ostream& o);

private:
    std::vector<std::string> scriptVector;
    void ScriptConverter::removeTempFile(std::ofstream& file);
};
