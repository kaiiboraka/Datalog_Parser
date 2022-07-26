#pragma once

#include "Helper.h"
#include "Token.h"
using namespace Tokens;

class Parameter
{
	string value;
	bool constant;
public:
	Parameter() = default;
	explicit Parameter(const string& value) : value(value)
	{
		constant = IsConstant(value);
	}

	void SetValue(const string& value);

	[[nodiscard]] const string& ToString() const;

	Parameter operator=(const string& other)
	{
		return Parameter{other};
	}
	const bool& isConstant() const
	{
		return constant;
	}
	static bool IsConstant(const string& other)
	{
		return (other.front() == '\'' && other.back() == '\'');
	}
	bool operator==(const string& other)
	{
		return this->value == other;
	}
	bool operator!=(const string& other)
	{
		return this->value != other;
	}
	operator string() const
	{
		return value;
	}
};

