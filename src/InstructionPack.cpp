#include "InstructionPack.hpp"
#include "Lexer.hpp"

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

        void InstructionPack::print_amd64(std::ostream& out)
        {
            switch (type_)
            {
            case Lexer::Token::LEFT:
                out << "    sub  rbx, 0d" << amount_ << std::endl;
                break;
            case Lexer::Token::RIGHT:
                out << "    add  rbx, 0d" << amount_ << std::endl;
                break;
            case Lexer::Token::PLUS:
                out << "    add  BYTE [rbx], 0d" << amount_ << std::endl;
                break;
            case Lexer::Token::MINUS:
                out << "    sub  BYTE [rbx], 0d" << amount_ << std::endl;
                break;
            case Lexer::Token::READ:
                for (unsigned int i = 0; i < amount_; i++)
                    out << "    call bf_input" << std::endl;
                break;
            case Lexer::Token::WRITE:
                for (unsigned int i = 0; i < amount_; i++)
                    out << "    call bf_output" << std::endl;
                break;
            default:
                break; // Should not happen
            }
        }

        void InstructionPack::print_c(std::ostream& out, unsigned int indentation)
        {
            std::string indent(4 * indentation, ' ');
            
            switch (type_)
            {
            case Lexer::Token::LEFT:
                out << indent << "ptr -= " << amount_ << ";" << std::endl;
                break;
            case Lexer::Token::RIGHT:
                out << indent << "ptr += " << amount_ << ";" << std::endl;
                break;
            case Lexer::Token::PLUS:
                out << indent << "*ptr += " << amount_ << ";" << std::endl;
                break;
            case Lexer::Token::MINUS:
                out << indent << "*ptr -= " << amount_ << ";" << std::endl;
                break;
            case Lexer::Token::READ:
                for (unsigned int i = 0; i < amount_; i++)
                    out << indent << "*ptr = bf_input();" << std::endl;
                break;
            case Lexer::Token::WRITE:
                for (unsigned int i = 0; i < amount_; i++)
                    out << indent << "bf_output(*ptr);" << std::endl;
                break;
            default:
                break; // Should not happen.
            }
        }

        void InstructionPack::prettyprint(std::ostream& out, unsigned int indentation)
        {
            out << std::string(4 * indentation, ' ');
            print(out);
            out << std::endl;
        }
    }
}
