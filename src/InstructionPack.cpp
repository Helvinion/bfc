#include "InstructionPack.h"
#include "Lexer.h"

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

        void InstructionPack::print(std::ostream& out)
        {
            for (unsigned int i = 0; i < amount_; i++)
                out << Lexer::convert(type_);
        }

        void InstructionPack::prettyprint(std::ostream& out, unsigned int indentation)
        {
            out << std::string(4 * indentation, ' ');
            print(out);
            out << std::endl;
        }
    }
}
