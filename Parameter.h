#pragma once
#include "Helper.h"

class Parameter
{
	string value;
public:
	Parameter() = default;
	explicit Parameter(const string& value)
		: value(value) {}

	[[nodiscard]] const string& ToString() const;
	void SetValue(const string& value);
};

