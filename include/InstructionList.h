#pragma once

#include <vector>

#include "AstNode.h"
#include "Pack.h"

namespace BF
{
	namespace AST
	{
		class InstructionList : public AstNode
		{
		public:
			virtual void parse(Lexer& lexer);
		private:
			std::vector<Pack*> instructions_;
		};
	}
}
