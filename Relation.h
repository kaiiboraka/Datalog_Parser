#pragma once
#include "Helper.h"
#include "Tuple.h"
#include <set>

class Relation
{
private:
	string name;
	Header header;
	set<Tuple> tuples;
public:
	Relation() = default;

	[[nodiscard]] const string& GetName() const;
	[[nodiscard]] const Header& GetHeader() const;
	[[nodiscard]] const set<Tuple>& GetTuples() const;
	void SetName(const string& name);
	void SetHeader(const Header& header);
	void SetTuples(const set<Tuple>& tuples);

	void AddTuple(Tuple t)
	{
		tuples.insert(t);
	}

	string ToString()
	{
		stringstream out;
		for (Tuple t : tuples)
		{
			if (t.size() > 0)
			{
				out << t.ToString() << endl;
			}
		}
		return out.str();
	}

	Relation Select(unsigned int col, const string& value)
	{
		Relation output;
		output.SetHeader(this->header);
		output.SetName("SELECT(" + this->name + ")");

		for (Tuple t : tuples)
		{
			if (t.at(col) == value)
			{
				output.AddTuple(t);
			}
		}
		return output;
	}


	Relation Select(unsigned int col1, unsigned int col2)
	{
		Relation output;
		output.SetHeader(this->header);
		output.SetName("SELECT(" + this->name + ")");

		for (Tuple t : tuples)
		{
			if (t.at(col1) == t.at(col2))
			{
				output.AddTuple(t);
			}
		}
		return output;
	}

	Relation Rename(unsigned int colToRename, const string& newName)
	{
		Relation output;
		output.SetName(name);

		Header newHeader = header;

		newHeader.at(colToRename) = newName;

		output.SetHeader(newHeader);
		output.SetTuples(tuples);

		return output;
	}

	//pi_{BCD} R
	Relation Project(vector<unsigned int> colsToKeep)
	{
		// {3, 2}
		//set name to something?
		// create a new header(empty)
		// fill it with the reordered data
		// (A B C D E) -> (D, C)
		// put header into the output relation

		// for each tuple t
		// new empty tuple
		// fill with reordered data
		// (1 2 3 4 5) -> (4, 3)
		// put that tuple into output relation

	}

};