#include "Parser.h"
#include "Relation.h"
#include <fstream>

const string ROOT_PATH = "../";
const string ARGS_PATH_A = "Project2aPassOffCases/2-80/";
const string ARGS_PATH_B = "Project2bPassOffCases/2-80/";
const string FILE_PATH = ROOT_PATH + "input.txt";

string TryReadFile(const string& path = FILE_PATH);

string TryReadArgs(const string& argv, char which);

int main(int argc, char* argv[])
{
//	string input = (argc > 1) ?
//				   TryReadArgs(argv[1], 'b') :
//				   TryReadFile();
//
//	Lexer l;
//	Parser parser(l.Run(input));
//
//	//DEBUG_MSG(parser.Run().ToString());
//	parser.Run();

	Tuple t1;
	t1.push_back("A");
	t1.push_back("B");
	t1.push_back("C");

	Tuple t2;
	t2.push_back("1");
	t2.push_back("2");
	t2.push_back("1");

	Header h1;
	h1.push_back("col0");
	h1.push_back("col1");
	h1.push_back("col2");


	ColumnNums colsToKeep;
	colsToKeep.push_back(2);
	colsToKeep.push_back(0);


	Relation r1;
	r1.SetName("first");
	r1.SetHeader(h1);
	r1.AddTuple(t1);
	r1.AddTuple(t2);

	cout << r1.Project(colsToKeep)->ToString() << endl;

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

