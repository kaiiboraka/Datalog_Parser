#pragma once
#include <set>
#include "Lexer.h"
#include "Parser.h"
#include "Output.h"
#include "Rule.h"

class DatalogProgram
{
	Lexer lexer;
	Parser parser;

	vector<Predicate> schemes;
	vector<Predicate> facts;
	vector<Rule> rules;
	vector<Predicate> queries;
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

	vector<Token> LexTokens(const string& input);
	void TryParse(const vector<Token>& tokens, ostream& os);

	[[nodiscard]] const vector<Predicate>& GetSchemes() const;
	[[nodiscard]] const vector<Predicate>& GetFacts() const;
	[[nodiscard]] const vector<Rule>& GetRules() const;
	[[nodiscard]] const vector<Predicate>& GetQueries() const;
	[[nodiscard]] const set<string>& GetDomain() const;

	void SetSchemes(const vector<Predicate>& schemes);
	void SetFacts(const vector<Predicate>& facts);
	void SetRules(const vector<Rule>& rules);
	void SetQueries(const vector<Predicate>& queries);
	void SetDomain(const set<string>& domain);

	void AddScheme(const Predicate& scheme);
	void AddFact(const Predicate& fact);
	void AddRule(const Rule& rule);
	void AddQuery(const Predicate& query);
	void AddStringToDomain(const string& newString);

	string ToString();

	void PrintTokens(ostream& out, const vector<TokenType>& types);
	vector<string> GetStrings(vector<Predicate> predicates);
	vector<string> GetStrings(vector<Rule> rules);
	vector<string> GetStrings();
	Output DetermineOutput(const TokenType& type);
};
