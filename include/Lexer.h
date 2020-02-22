#pragma once

#include <istream>

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
	private:

		Token convert(char c);

		std::istream& input_;
	};
}
