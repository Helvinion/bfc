#include "InstructionPack.h"
#include "Lexer.h";

namespace BF
{
	namespace AST
	{
		// Can only parse a set of consecutive instructions : + - < > , .
		void InstructionPack::parse(Lexer& lexer)
		{
			amount_ = 0;
			type_ = Lexer::Token::NONE;

			while (true)
			{
				Lexer::Token token = lexer.next();

				if (token == Lexer::Token::NONE)
					return; // Should not happen if amount == 0, but whatever
				
				if (type_ == Lexer::Token::NONE || type_ == token)
				{
					// Normal case: we count the amount of consecutive elements
					type_ = token;
					amount_++;
				}
				else
				{
					// Type is defined and different than token. This is the standard exit case
					lexer.put(token);
					return;
				}
			}
		}
	}
}