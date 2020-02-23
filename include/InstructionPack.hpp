#pragma once

#include "Pack.h"
#include "Lexer.h"

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
        private:
            Lexer::Token type_;
            unsigned int amount_;
        };
    }
}

