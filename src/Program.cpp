#include <sstream>

#include "Program.hpp"
#include "ParseError.hpp"

namespace BF
{
    namespace AST
    {
        // Parse everything.
        // We expect the lexer to be out of Tokens at the end of the operation
        void Program::parse(Lexer& lexer)
        {
            instructions_.parse(lexer);

            Lexer::Token token = lexer.next();

            if (token != Lexer::Token::NONE)
            {
                std::stringstream message;
                message << "Unexpected token at character " << lexer.location() << ": " << Lexer::convert(token);
                throw ParseError(message.str());
            }
        }

        void Program::print(std::ostream& out)
        {
            instructions_.print(out);
            out << std::endl;
        }

        void Program::print_c(std::ostream& out, unsigned int indentation)
        {
            (void)indentation;

            out << "#include <stdio.h>" << std::endl;
            out << std::endl;
            out << "int main()" << std::endl;
            out << "{" << std::endl;
            out << "    char array[30000] = {0};" << std::endl;
            out << "    char *ptr = array;" << std::endl;
            out << std::endl;
            instructions_.print_c(out, 1);
            out << "}" << std::endl;
        }

        void Program::prettyprint(std::ostream& out, unsigned int indentation)
        {
            instructions_.prettyprint(out, indentation);
        }
    }
}
