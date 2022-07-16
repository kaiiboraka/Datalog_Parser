//
// Created by Brandon on 7/14/2022.
//

#ifndef MAIN_CPP_INTERPRETER_H
#define MAIN_CPP_INTERPRETER_H
#include "DatalogProgram.h"
#include "Relation.h" // will be in database

class Interpreter
{
	DatalogProgram dp;
	// Database (Project 3) {map<string, relation*>}

public:
	Interpreter(DatalogProgram dp) : dp(dp)
	{

	}

	void Run()
	{
		EvaluateSchemes();
		EvaluateFacts();
		//evalRules(); // Project 4
		EvaluateQueries();
	}

	void EvaluateSchemes()
	{
		//defines a new table in our database
		//SNAP(A, B, C, D);
			// name: snap
			// header: {A, B, C, D}
	}
	void EvaluateFacts()
	{
		//adds a row to an existing table
		//SNAP('1','2','3','4')
			// add tuple ('1','2','3','4')
			// to the SNAP table
	}
	void EvaluateRules()
	{

	}
	void EvaluateQueries()
	{
		for(auto& query : dp.GetQueries())
		{
			EvaluatePredicate(query);
		}
	}

	Relation* EvaluatePredicate(Predicate p)
	{
		//SNAP('1', A, A, B)
		//select(0, '1')
		//select(1, 2)
	}
};


#endif //MAIN_CPP_INTERPRETER_H
