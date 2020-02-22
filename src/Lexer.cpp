#include "Lexer.h"

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

	Lexer::Token Lexer::next()
	{
		Token ret = Token::NONE;

		while (!input_.eof() && ret == Token::NONE)
		{
			char c = input_.get();
			if (input_.eof())
				return Token::NONE;
			ret = convert(c);
		}

		return ret;
	}
}

