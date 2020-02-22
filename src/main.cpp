#include <iostream>

#include "Lexer.h"

int main()
{
    BF::Lexer lexer(std::cin);

    while (true)
    {
        BF::Lexer::Token token = lexer.next();

        if (token == BF::Lexer::Token::NONE)
            return 0;
        
        switch (token)
        {
        case BF::Lexer::Token::LEFT:
            std::cout << "LEFT" << std::endl;
            break;
        case BF::Lexer::Token::RIGHT:
            std::cout << "RIGHT" << std::endl;
            break;
        case BF::Lexer::Token::PLUS:
            std::cout << "PLUS" << std::endl;
            break;
        case BF::Lexer::Token::MINUS:
            std::cout << "MINUS" << std::endl;
            break;
        case BF::Lexer::Token::OPEN:
            std::cout << "OPEN" << std::endl;
            break;
        case BF::Lexer::Token::CLOSE:
            std::cout << "CLOSE" << std::endl;
            break;
        case BF::Lexer::Token::READ:
            std::cout << "READ" << std::endl;
            break;
        case BF::Lexer::Token::WRITE:
            std::cout << "WRITE" << std::endl;
            break;
        default:
            break;
        }
    }
}
