#pragma once

#include <vector>

#include "AstNode.h"
#include "Pack.h"

namespace BF
{
    namespace AST
    {
        class InstructionList : public AstNode
        {
        public:
            virtual void parse(Lexer& lexer);
            virtual void prettyprint(std::ostream& out, unsigned int indentation = 0);
            virtual void print(std::ostream& out);

        private:
            std::vector<Pack*> instructions_;
        };
    }
}
