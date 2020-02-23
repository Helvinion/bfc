#include <iostream>

#include "Lexer.hpp"
#include "Program.hpp"
#include "ParseError.hpp"

int main()
{
    BF::Lexer lexer(std::cin);

    while (true)
    {
        BF::AST::Program program;
        bool             ok = true;

        try
        {
            program.parse(lexer);
        }
        catch (BF::ParseError& error)
        {
            std::cerr << "Parse error: " << error.what() << std::endl;
            ok = false;
        }

        if (ok)
        {
            program.print_c(std::cout);
            return 0;
        }
        else
        {
            std::cerr << "Parsing NOK" << std::endl;
            return 1;
        }
    }
}
