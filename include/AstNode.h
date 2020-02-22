#pragma once

#include "Lexer.h"

namespace BF
{
	namespace AST
	{
		class AstNode
		{
		public:
			virtual void parse(Lexer& lexer) = 0;
		};
	}
}
