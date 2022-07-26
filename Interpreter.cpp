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

	Clear();
}

void Interpreter::EvaluateSchemes()
{
	//defines a new table in our db
	//SNAP(A, B, C, D);
	// name: snap
	// header: {A, B, C, D}
	for (auto& scheme : datalogProgram.GetSchemes())
	{
//		auto* newRelation = new Relation{scheme, Header(scheme.GetParameterValues())};
//		database.AddRelation(*newRelation);
//		relations.insert(newRelation);
		database.AddRelation({scheme, Header(scheme.GetParameterValues())});
	}
}

void Interpreter::EvaluateFacts()
{
	//adds a row to an existing table
	//SNAP('1','2','3','4')
	// add tuple ('1','2','3','4')
	// to the SNAP table
	DatabaseMap & dbm = database.GetDB();
	for (Predicate fact : datalogProgram.GetFacts())
	{
		for (pair<string, Relation> table : dbm)
		{
			if (fact != table.first) continue; // else, if same
			dbm[fact].AddTuple(fact.GetParametersAsTuple());
		}
	}
}

void Interpreter::EvaluateRules()
{

}

void Interpreter::EvaluateQueries()
{
//	cout << "Query Evaluation" << endl;
	auto& DLqueries = datalogProgram.GetQueries();
	for (auto& queryString : DLqueries)
	{
		auto* query = new Relation(EvaluatePredicate(queryString));
		queries.push_back(query);
	}
	PrintQueries();
}

Relation Interpreter::EvaluatePredicate(const Predicate& query)
{
	auto& parameters = query.GetParameters();
	Relation result(database.GetRelation(query));
	map<string, Index> seenVars;
	ColumnNums colsToProject;
	ColumnNames newColumnNames;
	for (Index i = 0; i < parameters.size(); i++)
	{
		auto& currParam = parameters.at(i);
		DEBUG_MSG("\nResult size: "<<result.size());
		DEBUG_MSG("i: " << i);
		DEBUG_MSG("p: " << currParam.ToString());
		if (currParam.isConstant())
		{
			DEBUG_MSG("STRING");
			result = result.Select(i, currParam);
			DEBUG_MSG("After Select 1 - Result size: " << result.size()<<endl << result.ToString());
		}
		else
		{
			DEBUG_MSG("ID");
			// not seen already
			if(seenVars.find(currParam) == seenVars.end())
			{
				DEBUG_MSG("Never seen before");
				seenVars.insert({currParam, i});
				DEBUG_MSG("seenVars size: " << seenVars.size());
				colsToProject.push_back(i);
				DEBUG_MSG("colsToProject size: " << seenVars.size());
				newColumnNames.push_back(currParam);
				DEBUG_MSG("newColumnNames size: " << seenVars.size());
			}
			else // if seen already
			{
				DEBUG_MSG("Seen before");
				result = result.Select(seenVars[currParam], i);
				DEBUG_MSG("After Select 2 - Result size: "<<result.size());
			}
		}
	}
	result = result.Project(colsToProject);

	result = result.Rename(newColumnNames);

	return result;
}

void Interpreter::PrintQueries(ostream& out)
{
	Index i = 0;
	for(auto& query : queries)
	{
		out << datalogProgram.GetQueries()[i++].ToString() << "? ";
		string output = "No\n";
		if(!query->empty())
		{
			output = "Yes(" + to_string(query->size()) + ")\n";
			output += query->ToString();
		}
		out << output;
	}
}

void Interpreter::Clear()
{
	for (auto& q : queries)
	{
		delete q;
	}
}
