#pragma once

#include "Helper.h"
#include "Predicate.h"

typedef vector<string> Values;
typedef vector<string> ColumnNames;
typedef vector<unsigned int> ColumnNums;

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

	const ColumnNames& GetColumns() const
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

	string& at(unsigned int index)
	{
		Helper::CheckBounds(index, columns);
		return columns.at(index);
	}

	void push_back(string value)
	{
		columns.push_back(value);
	}

};