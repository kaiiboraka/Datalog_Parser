#include "DatalogProgram.h"
#include <fstream>

const string ROOT_PATH = "../";
const string ARGS_PATH = "Project2aPassOffCases/2-80/";
const string FILE_PATH = ROOT_PATH + "input.txt";

string TryReadFile(const string& path);

string TryReadArgs(const string& argv);

int main(int argc, char* argv[])
{
	DatalogProgram dp;

//	string input = (argc <= 1) ?
//				   TryReadFile(FILE_PATH) :
//				   TryReadArgs(argv[1]);
//
//	auto tokens = dp.LexTokens(input);
//
//	dp.TryParse(tokens, cout);

	Predicate snapScheme;
	snapScheme.SetName("snap");
	snapScheme.AddParameter("S");
	snapScheme.AddParameter("N");
	snapScheme.AddParameter("A");
	snapScheme.AddParameter("P");

	dp.AddScheme(snapScheme);

	cout << dp.ToString();

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

