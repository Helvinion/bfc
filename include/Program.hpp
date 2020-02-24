#pragma once

#include "InstructionList.hpp"
#include "AstNode.hpp"

/*
program:
    instruction_list

instruction_list:
    instruction_pack
    instruction_pack instruciton_list

instruction_pack:
    left_pack
    right_pack
    plus_pack
    minus_pack
    read_pack
    write_pack
    loop_pack

left_pack:
    left_token
    left_token left_pack

right_pack:
    right_token
    right_token right_pack

plus_pack:
    plus_token
    plus_token plus_pack

minus_pack:
    minus_token
    minus_token minus_pack

read_pack:
    read_token
    read_token read_pack

write_pack:
    write_token
    write_token write_pack

loop_pack:
    open_token instruction_list close_token

left_token: <

right_token: >

plus_token: +

minus_token: -

read_token: ,

write_token: .

open_token: [

close_token : ]

*/

namespace BF
{
    namespace AST
    {
        class Program : public AstNode
        {
        public:
            Program(const std::string& size = "30000");
            virtual void parse(Lexer& lexer);

            virtual void prettyprint(std::ostream& out, unsigned int indentation = 0);
            virtual void print_c(std::ostream& out, unsigned int indentation = 0);
            virtual void print(std::ostream& out);
            virtual void print_amd64(std::ostream& out);
        private:
            InstructionList instructions_;
            int size_memory_;
        };
    }
}
