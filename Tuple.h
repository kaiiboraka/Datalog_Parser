#pragma once

#include "Helper.h"
#include "Header.h"

class Tuple
{
	vector<string> values;

public:
	Tuple()
	{}

	Tuple(vector<string> values) : values(values)
	{}

	string ToString(Header header)
	{
		stringstream out;
		string sep = "";
		for (unsigned i = 0; i < size(); i++)
		{
			string name = header.at(i);
			string value = at(i);
			out << sep << name << "=" << value;
			sep = ",";
		}
		return out.str();
	}

	unsigned int size()
	{
		return values.size();
	}

	string at(unsigned int index)
	{
		return values.at(index);
	}

	void push_back(string value)
	{
		values.push_back(value);
	}

	//You must define this to allow tuples to be put into a set
	bool operator<(const Tuple t) const
	{
		return values < t.values;
	}

	// TODO: add more delegation functions as needed

};