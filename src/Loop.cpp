#include "Loop.h"
#include "ParseError.h"

namespace BF
{
	namespace AST
	{
		// Parse everything, but expect to find a closing token after it.
		void Loop::parse(Lexer& lexer)
		{
			instructions_.parse(lexer);

			Lexer::Token token = lexer.next();

			if (token != Lexer::Token::CLOSE)
				throw ParseError("Unclosed loop at the end of the input");
		}
	}
}