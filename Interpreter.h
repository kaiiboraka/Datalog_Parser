//
// Created by Brandon on 7/14/2022.
//

#ifndef MAIN_CPP_INTERPRETER_H
#define MAIN_CPP_INTERPRETER_H
#include "DatalogProgram.h"
#include "Relation.h" // will be in db
#include "Database.h"
#include "Graph.h"
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

	Relation* EvaluatePredicate(const Predicate& query);
	void PrintRule(const Rule& ruleToPrint, ostream& out = cout);
	void PrintQueries(ostream& out = cout);
	void Clear();
	static Relation* JoinIntermediates(const vector<Relation*>& intermediates);
	vector<Relation*> EvaluateRuleBody(const Rule& rule);
	Relation* ProjectBodyToHead(const Predicate& headPredicate, Relation* joined) const;
	Relation* RenameBodyToHead(const Relation& targetTable, Relation* joined) const;
	void ProcessRules(const Rules& rulesToProcess);
	static Rules ReverseRules(const Rules& oldRules);
	void ProcessRule(const Rule& rule);
};


#endif //MAIN_CPP_INTERPRETER_H
