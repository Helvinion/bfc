#include "Loop.hpp"
#include "ParseError.hpp"

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

        void Loop::print_amd64(std::ostream& out)
        {
            static unsigned int loop_id = 0;

            unsigned int my_id = loop_id;
            loop_id++;
            
            out << "loop" << my_id << ":" << std::endl;
            out << "    cmp  [rbx], BYTE 0" << std::endl;
            out << "    je   endloop" << my_id << std::endl;
            instructions_.print_amd64(out);
            out << "    cmp  [rbx], BYTE 0" << std::endl;
            out << "    jne   loop" << my_id << std::endl;
            out << "endloop" << my_id << ":" << std::endl;
        }

        void Loop::print_c(std::ostream& out, unsigned int indentation)
        {
            out << std::string(4 * indentation, ' ') << "while (*ptr)" << std::endl;
            out << std::string(4 * indentation, ' ') << "{" << std::endl;
            instructions_.print_c(out, indentation + 1);
            out << std::string(4 * indentation, ' ') << "}" << std::endl;
        }

        void Loop::prettyprint(std::ostream& out, unsigned int indentation)
        {
            out << std::string(4 * indentation, ' ') << "[" << std::endl;
            instructions_.prettyprint(out, indentation + 1);
            out << std::string(4 * indentation, ' ') << "]" << std::endl;
        }
    }
}
