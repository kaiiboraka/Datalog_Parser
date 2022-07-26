#include "Parser.h"
#include "Relation.h"
#include "Interpreter.h"
#include <fstream>

const string ROOT_PATH = "../";
const string ARGS_PATH_A = "Project2aPassOffCases/2-80/";
const string ARGS_PATH_B = "Project2bPassOffCases/2-80/";
const string FILE_PATH = ROOT_PATH + "input.txt";

string TryReadFile(const string& path = FILE_PATH);

string TryReadArgs(const string& argv, char which);

void RunInterpreter(const string & input);

int main(int argc, char* argv[])
{
	string input = (argc > 1) ?
				   TryReadArgs(argv[1], 'b') :
				   TryReadFile();

	RunInterpreter(input);

	return 0;
}

string TryReadFile(const string& path)
{
	try
	{
		return Helper::ReadFileIntoString(path);
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
		return NULL;
	}
}

string TryReadArgs(const string& argv, char which)
{
	ifstream ifs(argv);
	if (!ifs.is_open())
	{
		string path = (which == 'a') ? ARGS_PATH_A : ARGS_PATH_B;

		ifs.open(path + argv);
	}

	string line, output;
	while (getline(ifs, line)) output += line + '\n';

	return output;
}

void RunInterpreter(const string & input)
{
	//	Lexer l(input);
	//	Parser p(l.Run());
	//	Interpreter i(p.Run());
	Interpreter interpreter(Parser(Lexer(input).Run()).Run());

	interpreter.Run();
}

