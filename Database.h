//
// Created by Brandon on 7/19/2022.
//

#ifndef MAIN_CPP_DATABASE_H
#define MAIN_CPP_DATABASE_H
#include "Helper.h"
#include "Relation.h"
typedef map<string, Relation> DatabaseMap;
class Database
{
	DatabaseMap databaseMap;
public:
	Database() = default;

	DatabaseMap& GetDB()
	{
		return databaseMap;
	}

	void AddRelation(const Relation& r)
	{
		databaseMap.insert({r.GetName(), r});
	}
};


#endif //MAIN_CPP_DATABASE_H
