//
// Created by Brandon on 7/14/2022.
//

#include "Interpreter.h"

void Interpreter::Run()
{
	EvaluateSchemes();
	EvaluateFacts();
	EvaluateRules(); // Project 4
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
	DatabaseMap& dbm = database.GetDB();
	for (Predicate fact : datalogProgram.GetFacts())
	{
		for (pair<string, Relation> table : dbm)
		{
			if (fact != table.first) continue; // else, if same
			dbm[fact].insert(fact.GetParametersAsTuple());
		}
	}
}

void Interpreter::EvaluateRules()
{
	// print rule
	cout << "Rule Evaluation" << endl;

	Count rowCount = 0;
	Count iterationCount = 0;
/*	auto& oldRules = datalogProgram.GetRules();

	auto reversedGraph = ReverseRules(oldRules);

	DFSGraph<Rule> ruleGraph{reversedGraph};

	auto nodes = ruleGraph.GetNodes();
	for (Index i = 0; i < nodes.size(); i++)
	{
		auto currentRule = ruleGraph.at(i).value;
		auto ruleBodySize = currentRule.GetBody().size();
		for (Index j = 0; j < ruleBodySize; j++)
		{
			nodes.at(i).push_back(currentRule.at(j) );
		}
	}*/
	do
	{
		rowCount = database.TotalRows();

		ProcessRules(datalogProgram.GetRules());
		iterationCount++;
		// print what's added to/changed in the relation

	}
	while (rowCount != database.TotalRows());
	cout << endl << "Schemes populated after " << iterationCount << " passes through the Rules." << endl << endl;
}

void Interpreter::ProcessRules(const Rules& rulesToProcess)
{
	for (auto& rule : rulesToProcess)
	{
		ProcessRule(rule);
	}
}

void Interpreter::ProcessRule(const Rule& rule)
{
	PrintRule(rule);

	Relation& targetTable = database.GetRelation(rule.GetHead());

	// Step 1: Evaluate the Predicates
	vector<Relation*> intermediates = EvaluateRuleBody(rule);

	// Step 2: Join the resulting Relations
	Relation* joined = JoinIntermediates(intermediates);

	// Step 3: Project the columns that appear in the head predicate
	// instead of targetTable, I want the rule's head's parameters
	// the columns to keep are the indexes in joined's columns overlap
	joined = ProjectBodyToHead(rule.GetHead(), joined);

	DEBUG_MSG("what's in the BOX " << joined->ToString());

	// Step 4: Rename
	joined = RenameBodyToHead(targetTable, joined);
	DEBUG_MSG("what's in the RENAME " << joined->ToString());
	// Step 5: Union with the relation in the database
	targetTable.Union(joined);
}

//R0: R1, R2
//R1: R0, R2
//R2: R3, R4
//R3: R2
//R4:
// turns into
//R0: R1
//R1: R0
//R2: R0, R1, R3
//R3: R2
//R4: R2
Rules Interpreter::ReverseRules(const Rules& oldRules)
{
	Rules reversedRules;
	for (auto oldRule = oldRules.begin(); oldRule != oldRules.end(); oldRule++)
	{// for each old rule
		Rule newRule = *oldRule;
		for (const Rule& jRuleInList : oldRules)
		{// go through all the rules
			Predicates newBody;
			auto& jRuleBody = jRuleInList.GetBody();
			for (auto& jRulePred : jRuleBody)
			{
				//ask them if i am in their body
				if (jRulePred == string(oldRule->GetHead()))
				{
					newBody.push_back(jRuleInList.GetHead());
					break;
				}
			}
			newRule.SetBody(newBody);
		}
		reversedRules.insert(newRule);
	}

	return reversedRules;
}

Relation* Interpreter::ProjectBodyToHead(const Predicate& headPredicate, Relation* joined) const
{
	HeaderOverlap overlap = HeaderOverlap::FindHeaderOverlap(headPredicate, joined->GetHeader());

	return joined->Project(overlap.numsInCommon);
}

Relation* Interpreter::RenameBodyToHead(const Relation& targetTable, Relation* joined) const
{
	auto targetColumns = targetTable.GetHeader().GetColumns();
	if (Debugger::enabled)
	{
		for (auto column: targetColumns)
		{
			DEBUG_MSG("column: " << column);
		}
	}
	return joined->Rename(targetColumns);
}

vector<Relation*> Interpreter::EvaluateRuleBody(const Rule& rule)
{
	vector<Relation*> intermediates;
	for (auto& dependency : rule.GetBody())
	{
		intermediates.push_back(EvaluatePredicate(dependency));
	}
	return intermediates;
}

Relation* Interpreter::JoinIntermediates(const vector<Relation*>& intermediates)
{
	if (intermediates.size() == 1)
	{
		return intermediates[0];
	}
	else if (intermediates.size() > 1)
	{
		auto* joined = intermediates[0]->NaturalJoin(intermediates[1]);
		for (Index i = 2; i < intermediates.size(); i++)
		{
			joined = joined->NaturalJoin(intermediates[i]);
		}

		return joined;
	}
	else
	{
		throw invalid_argument("Rule body requires at least 1 predicate");
	}
}

void Interpreter::EvaluateQueries()
{
	cout << "Query Evaluation" << endl;
	auto& DLqueries = datalogProgram.GetQueries();
	for (auto& queryString : DLqueries)
	{
		queries.push_back(EvaluatePredicate(queryString));
	}
	PrintQueries();
}

Relation* Interpreter::EvaluatePredicate(const Predicate& query)
{
	auto& parameters = query.GetParameters();

	Relation* result = new Relation(database.GetRelation(query));
	map<string, Index> seenVars;
	ColumnNums colsToProject;
	ColumnNames newColumnNames;

	for (Index i = 0; i < parameters.size(); i++)
	{
		auto& currParam = parameters.at(i);

		if (currParam.isConstant())
		{
			result = result->Select(i, currParam);
		}
		else
		{
			// not seen already
			if (seenVars.find(currParam) == seenVars.end())
			{
				seenVars.insert({currParam, i});
				colsToProject.push_back(i);
				newColumnNames.push_back(currParam);
			}
			else // if seen already
			{
				result = result->Select(seenVars[currParam], i);
			}
		}
	}
	result = result->Project(colsToProject);

	result = result->Rename(newColumnNames);

	return result;
}

void Interpreter::PrintRule(const Rule& ruleToPrint, ostream& out)
{
	out << ruleToPrint.ToString() << ".\n";
}

void Interpreter::PrintQueries(ostream& out)
{
	Index i = 0;
	for (auto& query : queries)
	{
		out << datalogProgram.GetQueries()[i++].ToString() << "? ";
		string output = "No\n";
		if (!query->empty())
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
