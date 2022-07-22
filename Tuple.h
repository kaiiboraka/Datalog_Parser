#pragma once

#include "Helper.h"
#include "Header.h"


class Tuple
{
	Values values;

public:
	Tuple()
	{}

	Tuple(const Values& values) : values(values)
	{}

	string ToString(Header header)
	{
		if (size() != header.size())
		{
			throw "sizes do not match";
		}
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
		Helper::CheckBounds(index, values);

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

	const Values& GetValues() const
	{
		return values;
	}

	void SetValues(const Values& values)
	{
		this->values = values;
	}



	// TODO: add more delegation functions as needed

};