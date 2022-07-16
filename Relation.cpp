#include "Relation.h"

Relation::Relation(const string& newName) : name(newName)
{

}


Relation::Relation(const Relation* other, const string& which)
{
	string instruction = Helper::GetLower(which);

	if (instruction == "select")
	{
		name = "SELECT(" + other->GetName() + ")";
		header = other->GetHeader();
	}
	if (instruction == "project")
	{
		name = "PROJECT(" + name + ")";
	}
}

Relation::Relation(const Relation* other, const Header& newHeader)
	: name(other->GetName()), header(newHeader), tuples(other->GetTuples())
{

}

Relation::Relation(const string& newName, const Header& newHeader, const Tuples& newTuples)
	: name(newName), header(newHeader), tuples(newTuples)
{

}

Relation* Relation::Select(unsigned int colIdx, const string& expectedValue)
{
	Helper::CheckBounds(colIdx, header.GetColumns());
	//	output.SetHeader(this->header);
	//	output.SetName("SELECT(" + this->name + ")");
	Relation* output = new Relation(this, "select");

	for (Tuple t : tuples)
	{
		if (t.at(colIdx) == expectedValue)
		{
			output->AddTuple(t);
		}
	}
	return output;
}

Relation* Relation::Select(unsigned int col1, unsigned int col2)
{
	Helper::CheckBounds(col1, header.GetColumns());
	Helper::CheckBounds(col2, header.GetColumns());
	//	output.SetHeader(this->header);
	//	output.SetName("SELECT(" + this->name + ")");
	Relation* output = new Relation(this, "select");

	for (Tuple t : tuples)
	{
		if (t.at(col1) == t.at(col2))
		{
			output->AddTuple(t);
		}
	}
	return output;
}

/*
	Relation output;
	output.SetName(name);

	Header newHeader = header;

	newHeader.at(colToRename) = newName;

	output.SetHeader(newHeader);
	output.SetTuples(tuples);

	return output;
*/
Relation* Relation::Rename(unsigned int colToRename, const string& newName)
{
	Header newHeader = header;
	newHeader.at(colToRename) = newName;

	return new Relation(this, newHeader);
}

Relation* Relation::Rename(const ColumnNames& newColumns)
{
	return new Relation(this, Header(newColumns));
}

/*
	 S N A P
	 '0', '1', '2', '3'
	 'a','b' 'c' 'd'
	 project ({2, 3})
	 A, P
	 2, 3
	 c, d
	 project ({3, 0})
	 P, S
	 3, 0
	 d, a
	Relation* output = new Relation(this, "project");

	 {3, 2}
	set name to something?
	 for each int i in colsToKeep
	 add oldHeader.at(i) to new header
	 (A B C D E) -> (D, C)
	 put header into the output relation*

	 set tuples
	 foreach tuple t
	 make a new empty tuple
	 for each int i in colsToKeep
	 add t.at(i) into the new empty tuple
	 add newTuple into output relation
	 (1 2 3 4 5) -> (4, 3)
*/
Relation* Relation::Project(const ColumnNums& colsToKeep)
{
	Header newHeader;
	Tuples newTuples;
	for (auto& i : colsToKeep)
	{
		newHeader.push_back(this->header.at(i));
	}
	for (Tuple t : tuples)
	{
		Tuple newTuple;
		for (auto& i : colsToKeep)
		{
			newTuple.push_back(t.at(i));
		}
		newTuples.insert(newTuple);
	}

	return new Relation(name, newHeader, newTuples);
}

void Relation::AddTuple(Tuple t)
{
	tuples.insert(t);
}

const string& Relation::GetName() const
{
	return name;
}

const Header& Relation::GetHeader() const
{
	return header;
}

const set<Tuple>& Relation::GetTuples() const
{
	return tuples;
}

void Relation::SetName(const string& name)
{
	Relation::name = name;
}

void Relation::SetHeader(const Header& header)
{
	Relation::header = header;
}

void Relation::SetTuples(const set<Tuple>& tuples)
{
	Relation::tuples = tuples;
}

string Relation::ToString()
{
	stringstream out;
	for (Tuple t : tuples)
	{
		if (t.size() > 0)
		{
			out << t.ToString(header) << endl;
		}
	}
	return out.str();
}
