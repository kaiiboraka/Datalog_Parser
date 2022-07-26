#pragma once

#include "DatalogProgram.h"
#include "Token.h"

using namespace Tokens;

class Parser
{
	static const Index NEXT = 1;

	vector<Token> tokens;
	DatalogProgram dp;
public:
	const DatalogProgram& GetDatalogProgram() const;
private:

	Index currTokenIdx, step;

	vector<TokenType> steps =
		{
			SCHEMES,
			FACTS,
			RULES,
			QUERIES,
			END_OF_FILE
		};

public:

	Parser() = default;

	explicit Parser(const vector<Token>& tokens);

	string PrevTokenString();

	string CurrTokenString();

	string PrintTypeFromTokens(int offset);

	[[nodiscard]] TokenType CurrTokenType();

	void AdvanceToken();

	void ThrowError(bool problem);

	void Match(TokenType expectedType);

	[[maybe_unused]] void CheckForComments();

	void RemoveComments();

	void PrintStep();

	void PrintStart(const string& funcName, const string& grammar);

	void PrintEnd(const string& funcName) ;

	DatalogProgram& Run(ostream& os = cout);

	/*
	datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON factList
	 					RULES COLON ruleList QUERIES COLON query queryList EOF

	schemeList		->	scheme schemeList | lambda
	factList		->	fact factList | lambda
	ruleList		->	rule ruleList | lambda
	queryList		->	query queryList | lambda

	scheme   		-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
	fact    		->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
	rule    		->	headPredicate COLON_DASH predicate predicateList PERIOD
	query	        ->  predicate Q_MARK

	headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
	predicate		->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN

	predicateList	->	COMMA predicate predicateList | lambda
	parameterList	-> 	COMMA parameter parameterList | lambda
	stringList		-> 	COMMA STRING stringList | lambda
	idList  		-> 	COMMA ID idList | lambda
	parameter		->	STRING | ID
 	*/

	void Datalog();

	void ParseScheme();

	void ParseIDList(Predicate& currPred);

	void ParseSchemeList();

	void ParseFact();

	void ParseStringList(Predicate& currPred);

	void ParseFactList();

	void ParseRule();

	Predicate ParseHeadPredicate();

	Predicate ParsePredicate();

	Parameter ParseParameter();

	void ParseParameterList(Predicate& currPred);

	void ParsePredicateList(Rule& currRule);

	void ParseRuleList();

	void ParseQuery();

	void ParseQueryList();


	const string& PrevTokenValue();
};
