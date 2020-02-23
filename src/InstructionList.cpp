#include "InstructionList.hpp"
#include "InstructionPack.hpp"
#include "Loop.hpp"

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
        
        void InstructionList::print(std::ostream& out)
        {
            for (unsigned int i = 0; i < instructions_.size(); i++)
                instructions_[i]->print(out);
        }

        void InstructionList::print_amd64(std::ostream& out)
        {
            for (unsigned int i = 0; i < instructions_.size(); i++)
                instructions_[i]->print_amd64(out);
        }

        void InstructionList::print_c(std::ostream& out, unsigned int indentation)
        {
            for (unsigned int i = 0; i < instructions_.size(); i++)
                instructions_[i]->print_c(out, indentation);
        }

        void InstructionList::prettyprint(std::ostream& out, unsigned int indentation)
        {
            for (unsigned int i = 0; i < instructions_.size(); i++)
                instructions_[i]->prettyprint(out, indentation);
        }
    }
}
