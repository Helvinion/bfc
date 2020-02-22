#pragma once

#include "Pack.h"
#include "Lexer.h"

namespace BF
{
	namespace AST
	{
		class InstructionPack : public Pack
		{
		public:
			virtual void parse(Lexer& lexer);
		private:
			Lexer::Token type_;
			unsigned int amount_;
		};
	}
}

