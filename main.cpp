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

void Lab4();

int main(int argc, char* argv[])
{
	string input = (argc > 1) ?
				   TryReadArgs(argv[1], 'b') :
				   TryReadFile();

	RunInterpreter(input);
	//Lab4();

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
	while (getline(ifs, line))
	{
		output += line + '\n';
	}

	return output;
}

void RunInterpreter(const string & input)
{
	//	Lexer l(input);
	//	Parser p(l.Run());
	//	Interpreter i(p.Run());
	Interpreter(Parser(Lexer(input).Run()).Run()).Run();

}

void Lab4()
{
	Tuple snap_t1;
	snap_t1.push_back("33333");
	snap_t1.push_back("Snoopy");
	snap_t1.push_back("12 Apple St.");
	snap_t1.push_back("555-1234");

	Tuple snap_t2;
	snap_t2.push_back("12345");
	snap_t2.push_back("C. Brown");
	snap_t2.push_back("12 Apple St.");
	snap_t2.push_back("555-1234");

	Tuple snap_t3;
	snap_t3.push_back("22222");
	snap_t3.push_back("P. Patty");
	snap_t3.push_back("56 Grape Blvd");
	snap_t3.push_back("555-9999");


	Tuple csg_t1;
	csg_t1.push_back("cs101");
	csg_t1.push_back("12345");
	csg_t1.push_back("A");

	Tuple csg_t2;
	csg_t2.push_back("cs101");
	csg_t2.push_back("22222");
	csg_t2.push_back("B");

	Tuple csg_t3;
	csg_t3.push_back("cs101");
	csg_t3.push_back("33333");
	csg_t3.push_back("C");

	Tuple csg_t4;
	csg_t4.push_back("EE200");
	csg_t4.push_back("12345");
	csg_t4.push_back("B+");

	Tuple csg_t5;
	csg_t5.push_back("EE200");
	csg_t5.push_back("22222");
	csg_t5.push_back("B");

	Header h1;
	h1.push_back("StudentID");
	h1.push_back("Name");
	h1.push_back("Address");
	h1.push_back("Phone");

	Header h2;
	h2.push_back("Course");
	h2.push_back("StudentID");
	h2.push_back("Grade");

	Relation r1;
	r1.SetName("snap");
	r1.SetHeader(h1);
	r1.insert(snap_t1);
	r1.insert(snap_t2);
	r1.insert(snap_t3);

	Relation r2;
	r2.SetName("csg");
	r2.SetHeader(h2);
	r2.insert(csg_t1);
	r2.insert(csg_t2);
	r2.insert(csg_t3);
	r2.insert(csg_t4);
	r2.insert(csg_t5);

	cout << r1.NaturalJoin(&r2)->ToString() << endl << endl;
}