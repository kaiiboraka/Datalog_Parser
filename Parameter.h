#pragma once

#include "Helper.h"
#include "Token.h"
using namespace Tokens;

class Parameter
{
	string value;
public:
	Parameter() = default;
	explicit Parameter(const string& value)
		: value(value) {}

	void SetValue(const string& value);

	[[nodiscard]] const string& ToString() const;
};

