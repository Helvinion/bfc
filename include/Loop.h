#pragma once

#include "Pack.h"
#include "InstructionList.h"
#include "Lexer.h"

namespace BF
{
	namespace AST
	{
		class Loop : public Pack
		{
		public:
			virtual void parse(Lexer& lexer);
			virtual void print(std::ostream& out);
			virtual void prettyprint(std::ostream& out, unsigned int indentation);

		private:
			InstructionList instructions_;
		};
	}
}
