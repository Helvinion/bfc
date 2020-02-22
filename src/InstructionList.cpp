#include "InstructionList.h"
#include "InstructionPack.h"
#include "Loop.h"

namespace BF
{
	namespace AST
	{
		// Parse everything we can, choosing the type of each instruction group.
		// We may be inside one or several loop levels.
		void InstructionList::parse(Lexer& lexer)
		{
			while (true)
			{
				Lexer::Token token = lexer.next();

				if (token == Lexer::Token::NONE)
				{
					return;
				}
				else if (token == Lexer::Token::OPEN)
				{
					// This is a loop begining. We consume the Token and ask the Loop content to be parsed
					Loop* loop = new Loop();
					loop->parse(lexer);
					instructions_.push_back(loop);
				}
				else if (token == Lexer::Token::CLOSE)
				{
					// Not an error : it the end of the loop we may be into.
					lexer.put(token);
					return;
				}
				else
				{
					// Put back the Token, as we want the InstructionPack to parse it
					lexer.put(token);

					InstructionPack* pack = new InstructionPack();
					pack->parse(lexer);
					instructions_.push_back(pack);
				}
			}
		}
	}
}
