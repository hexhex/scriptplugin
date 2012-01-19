/* -*- C++ -*- */

/**
 * @file   ScriptAtom.cpp
 * @author Anton Korosec
 * @date   February 2007
 *
 * @brief  script-plugin for DLVHEX
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

#include "ScriptAtom.h"
#include "dlvhex2/Registry.h"
#include "dlvhex2/Term.h"

#include <unistd.h>
#include <cstdio>
#include <climits>
#include <cstring>
#include <sstream>
#include <cstdlib>

#include <sys/wait.h>

namespace dlvhex {
  namespace script {

	ScriptAtom::ScriptAtom() : PluginAtom("script", 0) {
		
		addInputConstant();
		setOutputArity(1);
	}


	void ScriptAtom::retrieve(const Query& query, Answer& answer) throw (PluginError) {
		
		Registry &registry = *getRegistry();
		std::string command = registry.terms.getByID(query.input[0]).getUnquotedString();

		ScriptProcess cp("ScriptAtom");

		std::stringstream dummyin;

		std::vector<std::string> args;
		args.push_back("sh");
		args.push_back("-c");
		args.push_back(command.c_str());

		std::stringstream &out = cp.execute(args, dummyin);

		do
		{
			std::string content;
			std::getline(out,content);

			if( content.empty() )
				break;

			bool isInt = true;
			Tuple tuple;

			char ch;
			for (int i=0; i<content.length(); i++) {
				ch = content.at(i);
				if (!::isdigit(ch)) 
					isInt = false;
			}

			if (isInt) {
				Term newterm(ID::MAINKIND_TERM | ID::SUBKIND_TERM_INTEGER, content);
				tuple.push_back(registry.storeTerm(newterm));
			} else {
				Term newterm(ID::MAINKIND_TERM, '"'+content+'"');
				tuple.push_back(registry.storeTerm(newterm));
			}

			// each tuple has only one term
			answer.get().push_back(tuple);
		}
		while( !out.fail() );

	}

  } // namespace script
} // namespace dlvhex
