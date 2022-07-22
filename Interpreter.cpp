//
// Created by Brandon on 7/14/2022.
//

#include "Interpreter.h"

void Interpreter::Run()
{
	EvaluateSchemes();
	EvaluateFacts();
	//evalRules(); // Project 4
	EvaluateQueries();
}

void Interpreter::EvaluateSchemes()
{
	//defines a new table in our db
	//SNAP(A, B, C, D);
	// name: snap
	// header: {A, B, C, D}
	for (auto& scheme : datalogProgram.GetSchemes())
	{
		auto* newRelation = new Relation{scheme, Header(scheme.GetParameterValues())};
		database.AddRelation(*newRelation);
		relations.insert(newRelation);
	}
}

void Interpreter::EvaluateFacts()
{
	//adds a row to an existing table
	//SNAP('1','2','3','4')
	// add tuple ('1','2','3','4')
	// to the SNAP table
	for (Predicate fact : datalogProgram.GetFacts())
	{
		DatabaseMap & dbm = database.GetDB();
		for (pair<string, Relation> relation : dbm)
		{
			if (fact != relation.first) continue; // else, if same
			dbm[fact].AddTuple(fact.GetParametersAsTuple());
		}
	}
}

void Interpreter::EvaluateRules()
{

}

void Interpreter::EvaluateQueries()
{
	for (auto& query : datalogProgram.GetQueries())
	{
		relations.insert(EvaluatePredicate(query));
	}
}

Relation* Interpreter::EvaluatePredicate(const Predicate& query)
{
	//SNAP('1', A, A, B)
	//select(0, '1')
	//select(1, 2)
	//dbm[queryPredicate]
	auto* queryTable = &database.GetDB()[query];
	auto& pList = query.GetParameters();
	Relation* result;

	for (int i = 0; i < pList.size(); i++)
	{
		if (pList.at(i).isConstant())
		{
			result = queryTable->Select(i, pList.at(i));
		}
	}
	return result;
}
