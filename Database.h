#pragma once
#include "Helper.h"
#include "Relation.h"
typedef map<string, Relation> DatabaseMap;
class Database
{
	DatabaseMap databaseMap;
public:
	Database() = default;

	Relation GetRelation(const string& query)
	{
		return databaseMap[query];
	}

	DatabaseMap& GetDB()
	{
		return databaseMap;
	}

	void AddRelation(const Relation& r)
	{
		databaseMap.insert({r.GetName(), r});
	}
};
