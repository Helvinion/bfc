#include <iostream>
#include <sstream>

#include "Program.hpp"
#include "ParseError.hpp"

namespace BF
{
    namespace AST
    {
        Program::Program(const std::string& size)
        {
            try
            {
                if (!size.empty())
                    size_memory_ = std::stoi(size, nullptr);
                else
                    size_memory_ = 30000;

                if (size_memory_ == 0)
                {
                    std::cerr << "Memory can't have a size of 0" << std::endl;
                    exit(4);
                }
            }
            catch (...)
            {
                std::cerr << "Invalid size given: " << size << std::endl;
                exit(4);
            }
        }
        
        // Parse everything.
        // We expect the lexer to be out of Tokens at the end of the operation
        void Program::parse(Lexer& lexer)
        {
            instructions_.parse(lexer);

            Lexer::Token token = lexer.next();

            if (token != Lexer::Token::NONE)
            {
                std::stringstream message;
                message << "Unexpected token at character " << lexer.location() << ": " << Lexer::convert(token);
                throw ParseError(message.str());
            }
        }

        void Program::print(std::ostream& out)
        {
            instructions_.print(out);
            out << std::endl;
        }

        void Program::print_amd64(std::ostream& out)
        {
            out << "    global main" << std::endl;
            out << "    extern exit, getchar, putchar, calloc, free" << std::endl;
            out << "    section .text" << std::endl;
            out << "main:" << std::endl;
            out << "    push rbp" << std::endl;
            out << "    mov  rbp, rsp" << std::endl;
            out << "    sub  rsp, 0d16" << std::endl;
            out << "    mov  esi, 0d1" << std::endl;
            out << "    mov  edi, 0d" << size_memory_ << std::endl;
            out << "    call calloc" << std::endl;
            out << "    mov [rbp - 8], rax" << std::endl;
            out << "    mov rbx, rax" << std::endl;
            out << std::endl;
            instructions_.print_amd64(out);
            out << std::endl;
            out << "    mov  rcx, [rbx]" << std::endl;
            out << "    mov  rbx, rcx" << std::endl;
            out << "    mov  rax, [rbp - 8]" << std::endl;
            out << "    mov  rdi, rax" << std::endl;
            out << "    call free" << std::endl;
            out << "    mov  rdi, rbx" << std::endl;
            out << "    call exit" << std::endl;
            out << "    pop rbp" << std::endl;
            out << "    ret" << std::endl;
        }

        void Program::print_c(std::ostream& out, unsigned int indentation)
        {
            (void)indentation;

            out << "#include <stdio.h>" << std::endl;
            out << "#include <stdlib.h>" << std::endl;
            out << std::endl;
            out << "int main()" << std::endl;
            out << "{" << std::endl;
            out << "    char ret = 0;" << std::endl;
            out << "    char *array = calloc(" << size_memory_ << ", 1);" << std::endl;
            out << "    char *ptr = array;" << std::endl;
            out << std::endl;
            instructions_.print_c(out, 1);
            out << std::endl;
            out << "    ret = *ptr;" << std::endl;
            out << "    free(array);" << std::endl;
            out << "    return ret;" << std::endl;
            out << "}" << std::endl;
        }

        void Program::prettyprint(std::ostream& out, unsigned int indentation)
        {
            instructions_.prettyprint(out, indentation);
        }
    }
}
