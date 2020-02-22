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

		void Loop::print(std::ostream& out)
		{
			out << "[";
			instructions_.print(out);
			out << "]";
		}

		void Loop::prettyprint(std::ostream& out, unsigned int indentation)
		{
			out << std::string(4 * indentation, ' ') << "[" << std::endl;
			instructions_.prettyprint(out, indentation + 1);
			out << std::string(4 * indentation, ' ') << "]" << std::endl;
		}
	}
}