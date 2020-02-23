#include "Lexer.hpp"

#include <string>

namespace BF
{
    Lexer::Lexer(std::istream& input)
        : input_(input)
    {
    }

    Lexer::Token Lexer::convert(char c)
    {
        switch (c)
        {
        case '<':
            return Token::LEFT;
        case '>':
            return Token::RIGHT;
        case '+':
            return Token::PLUS;
        case '-':
            return Token::MINUS;
        case '[':
            return Token::OPEN;
        case ']':
            return Token::CLOSE;
        case ',':
            return Token::READ;
        case '.':
            return Token::WRITE;
        default:
            return Token::NONE;
        }
    }

    std::string Lexer::convert(Token token)
    {
        switch (token)
        {
        case Token::LEFT:
            return "<";
        case Token::RIGHT:
            return ">";
        case Token::PLUS:
            return "+";
        case Token::MINUS:
            return "-";
        case Token::OPEN:
            return "[";
        case Token::CLOSE:
            return "]";
        case Token::READ:
            return ",";
        case Token::WRITE:
            return ".";
        case Token::NONE:
            return "EOF";
        default:
            return "???";
        }
    }

    Lexer::Token Lexer::next()
    {
        Token ret = Token::NONE;

        if (!stock_.empty())
        {
            ret = stock_.top();
            stock_.pop();
        }

        while (!input_.eof() && ret == Token::NONE)
        {
            char c = input_.get();
            if (input_.eof())
                return Token::NONE;
            ret = convert(c);
        }

        if (ret != Token::NONE)
            location_++;

        return ret;
    }

    void Lexer::put(Token token)
    {
        if (token != Token::NONE)
        {
            stock_.push(token);
            location_--;
        }
    }

    unsigned int Lexer::location()
    {
        return location_;
    }
}
