#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Token.h"
using namespace Tokens;

struct Output
{
	Output() = default;
	Output(const string& name, unsigned int size, const vector<string>& output, const string& suffix = "", const string& prefix = "")
		: name(name), size(size), output(output), suffix(suffix), prefix(prefix) {}

	friend ostream& operator << (ostream& out, const Output& self);
	friend istream& operator >> (istream& in, const Output& self);

	string name;
	unsigned int size = 0;
	vector<string> output;
	string suffix;
	string prefix;

};

