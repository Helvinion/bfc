#pragma once

#include "Pack.hpp"
#include "Lexer.hpp"

namespace BF
{
    namespace AST
    {
        class InstructionPack : public Pack
        {
        public:
            virtual void parse(Lexer& lexer);

            virtual void print(std::ostream& out);
            virtual void prettyprint(std::ostream& out, unsigned int indentation = 0);
            virtual void print_c(std::ostream& out, unsigned int indentation = 0);
        private:
            Lexer::Token type_;
            unsigned int amount_;
        };
    }
}

