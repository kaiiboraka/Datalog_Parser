#include "DatalogProgram.h"

void DatalogProgram::AddScheme(const Predicate& scheme)
{
	schemes.push_back(scheme);
}

void DatalogProgram::AddFact(const Predicate& fact)
{
	facts.push_back(fact);
}
void DatalogProgram::AddRule(const Rule& rule)
{
	rules.push_back(rule);
}
void DatalogProgram::AddQuery(const Predicate& query)
{
	queries.push_back(query);
}

void DatalogProgram::AddStringToDomain(const string& newString)
{
	domain.insert(newString);
}

string DatalogProgram::ToString()
{
	stringstream ss;

	PrintTokens(ss, order);

	return ss.str();
}

void DatalogProgram::PrintTokens(ostream& out, const vector<TokenType>& types)
{
	for (auto& t : types)
	{
		out << DetermineOutput(t);
	}
}

Output DatalogProgram::DetermineOutput(const TokenType& type)
{
	switch (type)
	{
		case SCHEMES:
			return Output(TokenNames[type], schemes.size(), GetStrings(schemes));
		case FACTS:
			return Output(TokenNames[type], facts.size(), GetStrings(facts), Symbols[PERIOD]);
		case RULES:
			return Output(TokenNames[type], rules.size(), GetStrings(rules), Symbols[PERIOD]);
		case QUERIES:
			return Output(TokenNames[type], queries.size(), GetStrings(queries), Symbols[Q_MARK]);
		case STRING:
			return Output("Domain", domain.size(), GetStrings());
		default:
			return Output{};
	}

	return Output();
}

vector<string> DatalogProgram::GetStrings(Predicates predicates)
{
	vector<string> output;
	for (auto& predicate : predicates)
	{
		output.push_back(predicate.ToString());
	}
	return output;
}

vector<string> DatalogProgram::GetStrings(Rules rules)
{
	vector<string> output;
	for (auto& rule : rules)
	{
		output.push_back(rule.ToString());
	}
	return output;
}

vector<string> DatalogProgram::GetStrings()
{
	vector<string> output;
	for (auto& string : domain)
	{
		output.push_back(string);
	}
	return output;
}
#ifndef __GNUC__
#pragma region Getters & Setters
#endif

const Predicates& DatalogProgram::GetSchemes() const
{
	return schemes;
}

const Predicates& DatalogProgram::GetFacts() const
{
	return facts;
}

const Rules& DatalogProgram::GetRules() const
{
	return rules;
}

const Predicates& DatalogProgram::GetQueries() const
{
	return queries;
}

const set<string>& DatalogProgram::GetDomain() const
{
	return domain;
}

void DatalogProgram::SetSchemes(const Predicates& schemes)
{
	DatalogProgram::schemes = schemes;
}

void DatalogProgram::SetFacts(const Predicates& facts)
{
	DatalogProgram::facts = facts;
}

void DatalogProgram::SetRules(const Rules& rules)
{
	DatalogProgram::rules = rules;
}

void DatalogProgram::SetQueries(const Predicates& queries)
{
	DatalogProgram::queries = queries;
}

void DatalogProgram::SetDomain(const set<string>& domain)
{
	DatalogProgram::domain = domain;
}

#ifndef __GNUC__
#pragma endregion
#endif
