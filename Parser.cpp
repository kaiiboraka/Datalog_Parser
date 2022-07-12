#include "Parser.h"

Parser::Parser(const vector<Token>& tokens)
	: tokens(tokens), currTokenIdx(0), step(0)
{
	currTokenIdx = 0;
	step = 0;
}

TokenType Parser::CurrTokenType()
{
	if (currTokenIdx >= tokens.size()) return UNDEFINED;
	return tokens.at(currTokenIdx).GetType();
}

void Parser::AdvanceToken()
{
	currTokenIdx++;
}

void Parser::ThrowError(bool problem = false)
{
	if (currTokenIdx >= tokens.size()) throw tokens.at(tokens.size() - 1);
	if (currTokenIdx < 0) throw Token("Out of bounds");
	if (problem) throw tokens.at(currTokenIdx);
}

string Parser::PrevTokenString()
{
	ThrowError();
	return tokens.at(currTokenIdx - 1).ToString();
}

string Parser::CurrTokenString()
{
	ThrowError();
	return tokens.at(currTokenIdx).ToString();
}

string Parser::PrintTypeFromTokens(int offset = 0)
{
	unsigned int idx = currTokenIdx + offset;
	if (idx >= tokens.size()) return TokenNames[END_OF_FILE];
	return to_string(idx) + ": " + TokenNames[tokens.at(idx).GetType()];
}

void Parser::Match(TokenType expectedType)
{
	DEBUG_MSG(">> " << __FUNCTION__ << "(" << TokenNames[expectedType] << ")");
	//the cout should be removed for the final project output
	DEBUG_MSG(setw(11) << "Current -- " << PrintTypeFromTokens());
	if (CurrTokenType() == expectedType)
	{
		// TODO: think about what should happen if the Parser matches an expected Token
		DEBUG_MSG("Matched " << PrintTypeFromTokens() << " with expected " << TokenNames[expectedType]);
		DEBUG_MSG(CurrTokenString());
		AdvanceToken();
		DEBUG_MSG(setw(8) << "Next " << PrintTypeFromTokens());
		DEBUG_MSG("<< end " << __FUNCTION__ << "(" << TokenNames[expectedType] << ")" << endl);
	}
	else
	{
		DEBUG_MSG("Token at index " << currTokenIdx << " was type: " << left << setw(12)
									<< TokenNames[CurrTokenType()]);
		DEBUG_MSG(" expected: " << TokenNames[expectedType]);
		// TODO: think about what should happen if the Parser matches an UN-expected Token
		ThrowError(true);
	}

}

void Parser::RemoveComments()
{
	for (int i = 0; i < tokens.size(); ++i)
	{
		if (tokens.at(i).GetType() == COMMENT)
		{
			tokens.erase(tokens.begin() + i);
		}
	}
}


[[maybe_unused]] void Parser::CheckForComments()
{
	if (CurrTokenType() == COMMENT)
	{
		DEBUG_MSG("> while (CurrTokenType() == COMMENT)");
		while (CurrTokenType() == COMMENT)
		{
			AdvanceToken();
			DEBUG_MSG(to_string(currTokenIdx - 1) << " advanced to -- " << PrintTypeFromTokens());
		}
		DEBUG_MSG("< break while");
	}
}

void Parser::PrintStep()
{
	DEBUG_MSG("step " << step << ": " << TokenNames[steps[step]]);
}

void Parser::PrintStart(const string& funcName, const string& grammar)
{
	DEBUG_MSG(">>> start " << funcName << "()");
	DEBUG_MSG(grammar << endl);
}

void Parser::PrintEnd(const string& funcName) const
{
	DEBUG_MSG("<<< end " << __FUNCTION__ << "()" << endl);
}

DatalogProgram Parser::Run()
{
	//TODO: call Start production function. should be datalog program
	DatalogProgram();
	return dp;
}

#ifndef __GNUC__
#pragma region Parsing Functions
#endif
#ifndef __GNUC__
#pragma region Full Grammar
#endif
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
#ifndef __GNUC__
#pragma endregion
#endif


// datalogProgram -> SCHEMES COLON scheme schemeList FACTS COLON factList
//					 RULES COLON ruleList QUERIES COLON query queryList EOF
void Parser::DatalogProgram()
{
	if (Debugger::enabled)
		PrintStart(__FUNCTION__,
				   "datalogProgram -> SCHEMES COLON scheme schemeList FACTS COLON factList\n"
				   "\tRULES COLON ruleList QUERIES COLON query queryList EOF");
	step = 0;
	if (Debugger::enabled) PrintStep();

	RemoveComments();

	Match(SCHEMES);
	Match(COLON);
	ParseScheme();
	ParseSchemeList();
	step++;
	if (Debugger::enabled) PrintStep();

	Match(FACTS);
	Match(COLON);
	ParseFactList();
	step++;
	if (Debugger::enabled) PrintStep();

	Match(RULES);
	Match(COLON);
	ParseRuleList();
	step++;
	if (Debugger::enabled) PrintStep();

	Match(QUERIES);
	Match(COLON);
	ParseQuery();
	ParseQueryList();
	step++;
	if (Debugger::enabled) PrintStep();

	Match(END_OF_FILE);
	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}

//	schemeList	->	scheme schemeList | lambda
//	factList	->	fact factList | lambda
//	ruleList	->	rule ruleList | lambda
//	queryList	->	query queryList | lambda

// schemeList -> scheme schemeList | lambda
void Parser::ParseSchemeList()
{
	if (Debugger::enabled) PrintStart(__FUNCTION__, "schemeList -> scheme schemeList | lambda");

	if (CurrTokenType() == steps.at(NEXT + step)) return;

	ParseScheme();
	ParseSchemeList();
	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}

// factList -> fact factList | lambda
void Parser::ParseFactList()
{
	if (Debugger::enabled) PrintStart(__FUNCTION__, "factList -> fact factList | lambda");

	if (CurrTokenType() == steps.at(NEXT + step))
	{ return; }

	ParseFact();
	ParseFactList();
	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}

// ruleList -> rule ruleList | lambda
void Parser::ParseRuleList()
{
	if (Debugger::enabled)PrintStart(__FUNCTION__, "ruleList -> rule ruleList | lambda");

	if (CurrTokenType() == steps.at(NEXT + step))
	{ return; }

	ParseRule();
	ParseRuleList();
	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}

// queryList -> query queryList | lambda
void Parser::ParseQueryList()
{
	if (Debugger::enabled)PrintStart(__FUNCTION__, "queryList -> query queryList | lambda");

	if (CurrTokenType() == steps.at(NEXT + step))
	{ return; }

	ParseQuery();
	ParseQueryList();
	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}

//	scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
//	fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
//	rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
//	query	    ->  predicate Q_MARK

// scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
void Parser::ParseScheme()
{
	if (Debugger::enabled)PrintStart(__FUNCTION__, "scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN");

	Predicate newScheme;

	Match(ID);
	newScheme.SetName(PrevTokenString());

	Match(LEFT_PAREN);
	Match(ID);
	newScheme.AddParameter(PrevTokenString());

	ParseIDList();



	Match(RIGHT_PAREN);

	dp.AddScheme(newScheme);

	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}

// fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
void Parser::ParseFact()
{
	if (Debugger::enabled)PrintStart(__FUNCTION__, "fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD");


	Match(ID);
	Match(LEFT_PAREN);
	Match(STRING);
	ParseStringList();
	Match(RIGHT_PAREN);
	Match(PERIOD);
	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}

// rule -> headPredicate COLON_DASH predicate predicateList PERIOD
void Parser::ParseRule()
{
	if (Debugger::enabled)PrintStart(__FUNCTION__, "rule -> headPredicate COLON_DASH predicate predicateList PERIOD");


	ParseHeadPredicate();
	Match(COLON_DASH);
	ParsePredicate();
	ParsePredicateList();
	Match(PERIOD);
	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}

//	query	    ->  predicate Q_MARK
void Parser::ParseQuery()
{
	if (Debugger::enabled)PrintStart(__FUNCTION__, "query -> predicate Q_MARK");


	ParsePredicate();
	Match(Q_MARK);
	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}


//	headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
//	predicate		->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN

//	headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
void Parser::ParseHeadPredicate()
{
	if (Debugger::enabled)PrintStart(__FUNCTION__, "headPredicate -> ID LEFT_PAREN ID idList RIGHT_PAREN");

	Match(ID);
	Match(LEFT_PAREN);
	Match(ID);
	ParseIDList();
	Match(RIGHT_PAREN);
	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}

//	predicate		->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
void Parser::ParsePredicate()
{
	if (Debugger::enabled)PrintStart(__FUNCTION__, "predicate -> ID LEFT_PAREN parameter parameterList RIGHT_PAREN");


	Match(ID);
	Match(LEFT_PAREN);
	ParseParameter();
	ParseParameterList();
	Match(RIGHT_PAREN);
	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}

//	predicateList	->	COMMA predicate predicateList | lambda
//	parameterList	-> 	COMMA parameter parameterList | lambda
//	stringList	-> 	COMMA STRING stringList | lambda
//	idList  	-> 	COMMA ID idList | lambda
//	parameter	->	STRING | ID
void Parser::ParsePredicateList()
{
	if (Debugger::enabled)PrintStart(__FUNCTION__, "predicateList -> COMMA predicate predicateList | lambda");

	if (CurrTokenType() != COMMA) return;

	Match(COMMA);
	ParsePredicate();
	ParsePredicateList();
	// else do nothing, lambda case
	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}

void Parser::ParseParameterList()
{
	if (Debugger::enabled)PrintStart(__FUNCTION__, "parameterList -> COMMA parameter parameterList | lambda");


	if (CurrTokenType() != COMMA) return;

	Match(COMMA);
	ParseParameter();
	ParseParameterList();

	// else do nothing, lambda case
	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}

void Parser::ParseParameter()
{
	if (Debugger::enabled)PrintStart(__FUNCTION__, "STRING | ID");

	switch (CurrTokenType())
	{
		case STRING: Match(STRING);
			return;
		case ID: Match(ID);
			return;
		default: return;
	}
	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}

void Parser::ParseStringList()
{
	if (Debugger::enabled)PrintStart(__FUNCTION__, "COMMA STRING stringList | lambda");

	if (CurrTokenType() != COMMA) return;

	Match(COMMA);
	Match(STRING);
	ParseStringList();
	// else do nothing, lambda case
	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}

void Parser::ParseIDList()
{
	if (Debugger::enabled)PrintStart(__FUNCTION__, "idList -> COMMA ID idList | lambda");

	if (CurrTokenType() != COMMA) return;

	Match(COMMA);
	Match(ID);

	ParseIDList();
	// else do nothing, lambda case
	if (Debugger::enabled) PrintEnd(__FUNCTION__);
}


