#pragma once
#include "Helper.h"
#include "Relation.h"
typedef map<string, Relation> DatabaseMap;
class Database
{
	DatabaseMap databaseMap;
	unsigned int rowCount;
public:
	Database()
	{
		TallyRows();
	}

	Relation& GetRelation(const string& tableName)
	{
		return databaseMap[tableName];
	}

	DatabaseMap& GetDB()
	{
		return databaseMap;
	}

	void AddRelation(const Relation& r)
	{
		databaseMap.insert({r.GetName(), r});
	}

	void TallyRows()
	{
		rowCount = 0;
		for(const auto& tablePair : databaseMap)
		{
			rowCount += tablePair.second.size();
		}
	}

	const unsigned int& TotalRows()
	{
		TallyRows();
		return rowCount;
	}
};
