#include "Lexer.h"
#include "Parser.h"
#include <fstream>

void TryParse(const vector<Token>& tokens, ostream& os);

string TryReadFile(const string& path);

string TryReadArgs(const string& argv);

const string ROOT_PATH = "../";
const string ARGS_PATH = "Project2aPassOffCases/2-80/";
const string FILE_PATH = ROOT_PATH + "input.txt";
int main(int argc, char* argv[])
{

	string input = (argc <= 1) ?
		TryReadFile(FILE_PATH) :
		TryReadArgs(argv[1]);

	Lexer lexer;
	vector<Token> tokens = lexer.Run(input);

	TryParse(tokens, cout);

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

string TryReadArgs(const string& argv)
{
	ifstream ifs(argv);
	if (!ifs.is_open()) ifs.open(ARGS_PATH + argv);
	string line, output;
	while (getline(ifs, line)) output += line + '\n';
	return output;
}

void TryParse(const vector<Token>& tokens, ostream& os)
{
	try
	{
		Parser parser = Parser(tokens);
		parser.Run();
		os << "Success!";
	}
	catch (Token& errorToken)
	{
		os << "Failure!" << endl << "  " << errorToken.ToString();
	}
}

