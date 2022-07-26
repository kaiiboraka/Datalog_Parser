#pragma once

#include "Helper.h"

#include "Parameter.h"

typedef vector<Parameter> Parameters;
typedef vector<string> Values;
typedef vector<string> ColumnNames;
typedef vector<Index> ColumnNums;
class Header
{
	ColumnNames columns;
public:
	Header() = default;
	Header(const ColumnNames& newColumns) : columns(newColumns)
	{}
//	Header(const Parameters& newColumns)
//	{
//		for (auto& p : newColumns)
//		{
//			columns.push_back(string(p));
//		}
//	}

	[[nodiscard]] const ColumnNames& GetColumns() const
	{
		return columns;
	}

	void SetColumns(const ColumnNames& newColumns)
	{
		Header::columns = newColumns;
	}

// Header :
	unsigned int size()
	{
		return columns.size();
	}

	string& at(Index index)
	{
		Helper::CheckBounds(index, columns);
		return columns.at(index);
	}

	void push_back(string value)
	{
		columns.push_back(value);
	}

	[[nodiscard]] string ToString() const
	{
		string output;
		for (auto& p : columns)
		{
			output += p + ", ";
		}
		return output;
	}

};