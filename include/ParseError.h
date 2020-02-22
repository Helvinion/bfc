#pragma once

#include <stdexcept>

namespace BF
{
	class ParseError : public std::logic_error
	{
		using std::logic_error::logic_error;
	};
}
