#include "Relation.h"

Relation::Relation(const string& newName) : name(newName)
{

}


Relation::Relation(const Relation* other, const string& which) :
	name(other->name)
{
	string instruction = Helper::GetLower(which);

	if (instruction.empty())
	{
		this->header = other->header;
		this->tuples = other->tuples;
	}
	else if (instruction == "select")
	{
		name = "SELECT(" + other->name + ")";
		header = other->header;
	}
	else if (instruction == "project")
	{
		name = "PROJECT(" + name + ")";
	}
}

Relation::Relation(const Relation* other, const Header& newHeader) :
	name(other->name),
	header(newHeader),
	tuples(other->tuples)
{

}

Relation::Relation(const string& newName, const Header& newHeader,
				   const Tuples& newTuples) :
	name(newName),
	header(newHeader),
	tuples(newTuples)
{

}

Relation Relation::Select(unsigned int colIdx, const string& expectedValue)
{
	Helper::CheckBounds(colIdx, header.GetColumns());
	//	output.SetHeader(this->header);
	//	output.SetName("SELECT(" + this->name + ")");
//	Relation output(this, "select");
	Relation output(name, header);

	for (Tuple t : tuples)
	{
		if (t.at(colIdx) == expectedValue)
		{
			output.AddTuple(t);
		}
	}
	DEBUG_MSG("Select 1:" << endl << output.ToString());
	return output;
}

Relation Relation::Select(unsigned int col1, unsigned int col2)
{
	Helper::CheckBounds(col1, header.GetColumns());
	Helper::CheckBounds(col2, header.GetColumns());
	//	output.SetHeader(this->header);
	//	output.SetName("SELECT(" + this->name + ")");
	//Relation output(this, "select");
	Relation output(name, header);
	for (Tuple t : tuples)
	{
		if (t.at(col1) == t.at(col2))
		{
			output.AddTuple(t);
		}
	}
	DEBUG_MSG("Select 2:" << endl << output.ToString());
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
Relation Relation::Rename(unsigned int colToRename, const string& newName)
{
	Header newHeader = header;
	newHeader.at(colToRename) = newName;

	return Relation{this, newHeader};
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
Relation Relation::Project(const ColumnNums& colsToKeep)
{
	Header newHeader;
	Tuples newTuples;
	for (auto& i : colsToKeep)
	{
		newHeader.push_back(this->header.at(i));
	}
	DEBUG_MSG("Old Header: " << this->header.ToString());
	DEBUG_MSG("New Header: " << newHeader.ToString());
	for (Tuple t : tuples)
	{
		Tuple newTuple;
		for (auto& i : colsToKeep)
		{
			newTuple.push_back(t.at(i));
		}
		newTuples.insert(newTuple);
	}
	auto rel = Relation(name, newHeader, newTuples);
	DEBUG_MSG(rel.ToString());
	return rel;
}

Relation Relation::Rename(const ColumnNames& newColumns)
{
	if (Debugger::enabled)
	{
		DEBUG_MSG("Renaming header to: ");
		string output = "   ";
		for (auto& p : newColumns)
		{
			output += p + ", ";
		}
		DEBUG_MSG(output);
	}
	return Relation{this, Header(newColumns)};
}

string Relation::ToString() const
{
	stringstream out;
	for (Tuple t : tuples)
	{
		if (!t.empty())
		{
			out << "  " << t.ToString(header) << endl;
		}
	}
	return out.str();
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

unsigned int Relation::size() const
{
	return tuples.size();
}

bool Relation::empty() const
{
	return tuples.empty();
}
