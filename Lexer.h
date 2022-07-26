#pragma once

#include "Automata.h"

class Lexer
{
	vector<Automaton*> automata;
	vector<string> lines;
	vector<Token> tokens;

	string input;

	void InitializeAutomata();

public:
	Lexer(const string & input = "") : input(input)
	{
		InitializeAutomata();
	}

	[[nodiscard]] const vector<Token>& GetTokens() const;

	vector<Token> Run();
	vector<Token> Run(const string& outsideInput);

	void PrintTokensList();

	static void TrimWhitespace(string& input, unsigned int& lineNum);

	void RunAutomata(string& input, unsigned int& lineNum);

	static void CompareResults(const string& input,
							   Automaton* currentAutomaton,
							   Automaton*& maxAutomaton,
							   unsigned int& maxRead);

	void AddToken(const Token& currToken);

	static void PrintToken(ostream& os, Token& currToken);
};

