#pragma once

#include "Helper.h"

class Header
{
	vector<string> attributes;

public:
	Header()
	{}

	Header(vector<string> attributes) : attributes(attributes)
	{}

// Header :
	unsigned int size()
	{
		return attributes.size();
	}

	string& at(unsigned int index)
	{
		return attributes.at(index);
	}

	void push_back(string value)
	{
		attributes.push_back(value);
	}

};