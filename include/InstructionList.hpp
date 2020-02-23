#pragma once

#include <vector>

#include "AstNode.hpp"
#include "Pack.hpp"

namespace BF
{
    namespace AST
    {
        class InstructionList : public AstNode
        {
        public:
            virtual void parse(Lexer& lexer);
            virtual void prettyprint(std::ostream& out, unsigned int indentation = 0);
            virtual void print_c(std::ostream& out, unsigned int indentation = 0);
            virtual void print(std::ostream& out);

        private:
            std::vector<Pack*> instructions_;
        };
    }
}
