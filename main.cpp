#include "Parser.h"
#include <fstream>

const string ROOT_PATH = "../";
const string ARGS_PATH = "Project2aPassOffCases/2-80/";
const string FILE_PATH = ROOT_PATH + "input.txt";

string TryReadFile(const string& path);

string TryReadArgs(const string& argv);

void TryParse(const vector<Token>& tokens, ostream& os = cout);

int main(int argc, char* argv[])
{

//	string input = (argc <= 1) ?
//				   TryReadFile(FILE_PATH) :
//				   TryReadArgs(argv[1]);
//
//	Lexer l;
//	auto tokens = l.Run(input);
//
//	TryParse(tokens);

	DatalogProgram program;

	Predicate snapScheme;
	snapScheme.SetName("snap");
	snapScheme.AddParameter("S");
	snapScheme.AddParameter("N");
	snapScheme.AddParameter("A");
	snapScheme.AddParameter("P");
	program.AddScheme(snapScheme);

	Predicate addressScheme;
	addressScheme.SetName("HasSameAddress");
	addressScheme.AddParameter("X");
	addressScheme.AddParameter("Y");
	program.AddScheme(addressScheme);

	Predicate snapFact;
	snapFact.SetName("snap");
	snapFact.AddParameter("\'12345\'");
	snapFact.AddParameter("\'C.Brown\'");
	snapFact.AddParameter("\'12 Apple\'");
	snapFact.AddParameter("\'555-1234\'");
	program.AddFact(snapFact);

	Rule addressRule;
	addressRule.SetHead(addressScheme);
	addressRule.AddPredicate(snapScheme);
	addressRule.AddPredicate(snapScheme);
	program.AddRule(addressRule);

	Predicate addressQuery;
	addressQuery.SetName("HasSameAddress");
	addressQuery.AddParameter("\'Snoopy\'");
	addressQuery.AddParameter("Who");
	program.AddQuery(addressQuery);

	program.AddStringToDomain("12 Apple");

	cout << program.ToString();

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
		os << "Success!" << endl;
	}
	catch (Token& errorToken)
	{
		os << "Failure!" << endl << "  " << errorToken.ToString() << endl;
	}
	catch (const string& errorMsg)
	{
		os << "Failure!" << endl << "  " << errorMsg << endl;
	}
}