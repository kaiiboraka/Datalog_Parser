#ifndef PARSER_H_DATALOG_H
#define PARSER_H_DATALOG_H

#include "Lexer.h"
#include "Parser.h"
#include <fstream>

const string ROOT_PATH = "../";
const string ARGS_PATH = "Project2aPassOffCases/2-80/";
const string FILE_PATH = ROOT_PATH + "input.txt";

void TryParse(const vector<Token>& tokens, ostream& os);

string TryReadFile(const string& path);

string TryReadArgs(const string& argv);

vector<Token> LexTokens(const string& input);

class Datalog
{
	Lexer lexer;
	Parser parser;

};

#endif //PARSER_H_DATALOG_H