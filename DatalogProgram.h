#pragma once

#include <set>
#include "Lexer.h"
#include "Output.h"
#include "Rule.h"
typedef vector<Predicate> Predicates;
typedef vector<Rule> Rules;
class DatalogProgram
{
	Predicates schemes;
	Predicates facts;
	Rules rules;
	Predicates queries;
	set<string> domain;
	vector<TokenType> order =
		{
			SCHEMES,
			FACTS,
			RULES,
			QUERIES,
			STRING
		};
public:
	DatalogProgram() = default;

	[[nodiscard]] const Predicates& GetSchemes() const;
	[[nodiscard]] const Predicates& GetFacts() const;
	[[nodiscard]] const Rules& GetRules() const;
	[[nodiscard]] const Predicates& GetQueries() const;
	[[nodiscard]] const set<string>& GetDomain() const;

	void SetSchemes(const Predicates& schemes);
	void SetFacts(const Predicates& facts);
	void SetRules(const Rules& rules);
	void SetQueries(const Predicates& queries);
	void SetDomain(const set<string>& domain);

	void AddScheme(const Predicate& scheme);
	void AddFact(const Predicate& fact);
	void AddRule(const Rule& rule);
	void AddQuery(const Predicate& query);
	void AddStringToDomain(const string& newString);

	string ToString();

	void PrintTokens(ostream& out, const vector<TokenType>& types);
	vector<string> GetStrings(Predicates predicates);
	vector<string> GetStrings(Rules rules);
	vector<string> GetStrings();
	Output DetermineOutput(const TokenType& type);
};
