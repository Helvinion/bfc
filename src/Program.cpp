#include <sstream>

#include "Program.hpp"
#include "ParseError.hpp"

namespace BF
{
    namespace AST
    {
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
            out << "    extern exit, getchar, putchar" << std::endl;
            out << "    section .text" << std::endl;
            out << "main:" << std::endl;
            out << "    push rbp" << std::endl;
            out << "    mov  rbp, rsp" << std::endl;
            out << "    sub  rsp, 0d30016" << std::endl;
            out << "    mov  rax, [fs:40]" << std::endl;
            out << "    mov  [rbp-8], rax" << std::endl;
            out << "    xor  eax, eax" << std::endl;
            out << "    mov  rbx, rsp" << std::endl;
            out << "    mov  rcx, rsp" << std::endl;
            out << "    add  rcx, 0d30000" << std::endl;
            out << "init:" << std::endl;
            out << "    mov  [rcx], DWORD 0" << std::endl;
            out << "    sub  rcx, 0d4" << std::endl;
            out << "    cmp  rcx, rbx" << std::endl;
            out << "    jne  init" << std::endl;
            out << std::endl;
            instructions_.print_amd64(out);
            out << std::endl;
            out << "    mov  rdi, [rbx]" << std::endl;
            out << "    call exit" << std::endl;
            out << "    pop rbp" << std::endl;
            out << "    ret" << std::endl;
        }

        void Program::print_c(std::ostream& out, unsigned int indentation)
        {
            (void)indentation;

            out << "#include <stdio.h>" << std::endl;
            out << std::endl;
            out << "int main()" << std::endl;
            out << "{" << std::endl;
            out << "    char array[30000] = {0};" << std::endl;
            out << "    char *ptr = array;" << std::endl;
            out << std::endl;
            instructions_.print_c(out, 1);
            out << std::endl;
            out << "    return *ptr;";
            out << "}" << std::endl;
        }

        void Program::prettyprint(std::ostream& out, unsigned int indentation)
        {
            instructions_.prettyprint(out, indentation);
        }
    }
}
