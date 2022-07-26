#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>

#include "Debugger.h"
typedef unsigned int Index;
using namespace std;

class Helper
{
public:
	static string ToCapitalized(const string& input)
	{
		char upperFirst = char(toupper(input.at(0)));
		string lowerRest = input.substr(1, input.size());
		transform(lowerRest.begin(), lowerRest.end(), lowerRest.begin(), ::tolower);
		return string() + upperFirst + lowerRest;
	}

	static string ReadFileIntoString(const string& path)
	{
		ifstream input_file(path);
		if (!input_file.is_open())
		{
			throw runtime_error("Could not open the file - '" + path + "'");
		}
		stringstream buffer;
		buffer << input_file.rdbuf();
		return buffer.str();
	}

	template<class T>
	static void CheckBounds(Index index, const vector<T> container)
	{
		if (index >= container.size()) throw out_of_range("Index out of bounds.");
	}


	template<class T>
	static void Test(const string& message, T const& expected, T const& observed)
	{
		try
		{
			cout << message << endl;
			cout << "Expected: >" << expected;
			cout << "< Observed: " << observed << endl;

			if (expected == observed)
			{
				cout << "Passed ✅" << endl;
			}
			else
			{
				cerr << "Failed ❌" << endl;
				throw invalid_argument(message);
			}
		}
		catch (exception& e)
		{
			cerr << e.what() << endl;
		}
	}

	static void ToLower(string& basicString)
	{
		for(auto& c : basicString)
		{
			c = char(tolower(c));
		}
	}
	static string GetLower(const string& basicString)
	{
		string output;
		for(auto& c : basicString)
		{
			output += char(tolower(c));
		}
		return output;
	}
};

