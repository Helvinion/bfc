#pragma once

#include <istream>
#include <stack>
#include <string>

namespace BF
{
    class Lexer
    {
    public:
        enum class Token
        {
            NONE,
            LEFT,
            RIGHT,
            PLUS,
            MINUS,
            OPEN,
            CLOSE,
            READ,
            WRITE
        };

        Lexer(std::istream& input);

        Token next();
        void  put(Token token);
        unsigned int location();

        static Token       convert(char c);
        static std::string convert(Token token);

    private:
        unsigned int      location_;
        std::istream&     input_;
        std::stack<Token> stock_;
    };
}
