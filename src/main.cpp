#include <iostream>

#include "Lexer.h"
#include "Program.h"
#include "ParseError.h"

int main()
{
    BF::Lexer lexer(std::cin);

    while (true)
    {
        BF::Lexer::Token token = lexer.next();
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
            std::cerr << "Parsing OK" << std::endl;
            return 0;
        }
        else
        {
            std::cerr << "Parsing NOK" << std::endl;
            return 1;
        }
    }
}
