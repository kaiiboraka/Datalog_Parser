//
// Created by Brandon on 7/14/2022.
//

#ifndef MAIN_CPP_INTERPRETER_H
#define MAIN_CPP_INTERPRETER_H
#include "DatalogProgram.h"
#include "Relation.h" // will be in db
#include "Database.h"
class Interpreter
{
	DatalogProgram datalogProgram;
	// Database (Project 3) {map<string, relation*>}
	Database database;
	vector<Relation*> queries;

public:
	Interpreter(const DatalogProgram& dp) : datalogProgram(dp)
	{

	}

	void Run();

	void EvaluateSchemes();
	void EvaluateFacts();
	void EvaluateRules();
	void EvaluateQueries();

	Relation EvaluatePredicate(const Predicate& query);
	void PrintQueries(ostream& out = cout);
	void Clear();
};


#endif //MAIN_CPP_INTERPRETER_H
