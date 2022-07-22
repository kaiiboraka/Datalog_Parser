#pragma once

#include "Helper.h"
#include "Token.h"
using namespace Tokens;

class Parameter
{
	string value;
public:
	Parameter() = default;
	Parameter(const string& value)
		: value(value) {}

	void SetValue(const string& value);

	[[nodiscard]] const string& ToString() const;

	Parameter operator=(const string& other)
	{
		return Parameter{other};
	}
	bool operator==(const string& other)
	{
		return this->value == other;
	}
	bool operator!=(const string& other)
	{
		return this->value != other;
	}
	explicit operator string() const
	{
		return value;
	}
};

