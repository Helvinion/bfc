#pragma once

#include "Pack.hpp"
#include "InstructionList.hpp"
#include "Lexer.hpp"

namespace BF
{
    namespace AST
    {
        class Loop : public Pack
        {
        public:
            virtual void parse(Lexer& lexer);
            virtual void print(std::ostream& out);
            virtual void print_amd64(std::ostream& out);
            virtual void prettyprint(std::ostream& out, unsigned int indentation);
            virtual void print_c(std::ostream& out, unsigned int indentation);

        private:
            InstructionList instructions_;
        };
    }
}
