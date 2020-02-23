#pragma once

#include <sstream>

#include "Lexer.h"

namespace BF
{
    namespace AST
    {
        class AstNode
        {
        public:
            virtual void parse(Lexer& lexer) = 0;
            virtual void prettyprint(std::ostream& out, unsigned int indentation = 0) = 0;
            virtual void print(std::ostream& out) = 0;
        };
    }
}
