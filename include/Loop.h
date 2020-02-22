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
		private:
			InstructionList instructions_;
		};
	}
}
