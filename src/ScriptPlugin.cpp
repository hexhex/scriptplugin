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
#include <dlvhex2/Logger.hpp>

#include <cstdlib>


namespace dlvhex {
  namespace script {

	ScriptPlugin::ScriptPlugin() : addToPath(""), converter(new ScriptConverter()) {
		setNameVersion(PACKAGE_TARNAME, SCRIPTPLUGIN_MAJOR, SCRIPTPLUGIN_MINOR, SCRIPTPLUGIN_MICRO);
	}


	ScriptPlugin::~ScriptPlugin() { 
	
	}


	PluginConverterPtr ScriptPlugin::createConverter(ProgramCtx& ctx) {
		  
		if (!converter->hasConverter()) {
			PluginConverterPtr pc;
			return pc;
		}
		return converter;
	}
	  
	  
	std::vector<PluginAtomPtr> ScriptPlugin::createAtoms(ProgramCtx&) const {
		
		std::vector<PluginAtomPtr> ret;
		ret.push_back(PluginAtomPtr(new ScriptAtom, PluginPtrDeleter<PluginAtom>()));
		return ret;

	}

	
	void ScriptPlugin::printUsage(std::ostream& out) {
		
		out << "Script-plugin: " << std::endl << std::endl;
		out << " --convert=SCRIPT Specify script for converting the input" << std::endl;
		out << " --addpath=PATH   Specify paths to prepend to the shell PATH " 
			<< "variable (searchpath for scripts)" << std::endl;
		return;
	}

	
	void ScriptPlugin::processOptions(std::list<const char*>& pluginOptions, ProgramCtx& ctx) {

		std::vector<std::list<const char*>::iterator> found;
		std::string::size_type o;
		std::string option;
    		
		for (std::list<const char*>::iterator it = pluginOptions.begin(); 
			 it != pluginOptions.end(); 
			 it++) 
		{

			option.assign(*it);
        	o = option.find("--convert=");
        	if (o != std::string::npos) {

           		converter->setConverter(option.substr(10));
				found.push_back(it);
           		continue;
        	}

        	o = option.find("--addpath=");
        	if (o != std::string::npos) {
				
           		this->addToPath = option.substr(10);
           		found.push_back(it);
           		continue;
        	}
    	}

    	for (std::vector<std::list<const char*>::iterator>::const_iterator it = found.begin(); 
			 it != found.end(); 
			 ++it) 
		{
        	pluginOptions.erase(*it);
    	}

		// immediately set the environment for the whole process,
    	// which is inherited by subprocesses.
    	if( !this->addToPath.empty() ) {
			// pre(!)pend path to existing PATH
			std::string path(::getenv("PATH"));
			if( path.empty() )
				path = this->addToPath;
			else 
				path = this->addToPath + ":" + path;
            LOG(INFO,"setting PATH to '" << path << "'");
			::setenv("PATH", path.c_str(), 1);
    	}
	}


	ScriptPlugin theScriptPlugin;
	
	

  } // namespace script
} // namespace dlvhex

IMPLEMENT_PLUGINVERSIONFUNCTION(SCRIPTPLUGIN_MAJOR,SCRIPTPLUGIN_MINOR,SCRIPTPLUGIN_MICRO);

extern "C"
void *PLUGINIMPORTFUNCTION() {
	return reinterpret_cast<void*>(& dlvhex::script::theScriptPlugin);
}

// vim:ts=4:
