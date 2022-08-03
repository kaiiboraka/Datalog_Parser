#include "Relation.h"

#ifndef __GNUC__
#pragma region Constructors
#endif

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

#ifndef __GNUC__
#pragma endregion
#endif

Relation* Relation::Select(unsigned int colIdx, const string& expectedValue)
{
	Helper::CheckBounds(colIdx, header.GetColumns());
	//	output.SetHeader(this->header);
	//	output.SetName("SELECT(" + this->name + ")");
//	Relation output(this, "select");
	Relation* output = new Relation(name, header);

	for (Tuple t : tuples)
	{
		if (t.at(colIdx) == expectedValue)
		{
			output->insert(t);
		}
	}
	//DEBUG_MSG("Select 1:" << endl << output->ToString());
	return output;
}

Relation* Relation::Select(unsigned int col1, unsigned int col2)
{
	Helper::CheckBounds(col1, header.GetColumns());
	Helper::CheckBounds(col2, header.GetColumns());
	//	output.SetHeader(this->header);
	//	output.SetName("SELECT(" + this->name + ")");
	//Relation output(this, "select");
	Relation* output = new Relation(name, header);
	for (Tuple t : tuples)
	{
		if (t.at(col1) == t.at(col2))
		{
			output->insert(t);
		}
	}
	//DEBUG_MSG("Select 2:" << endl << output->ToString());
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
Relation* Relation::Rename(Index colToRename, const string& newName)
{
	Header newHeader = header;
	newHeader.at(colToRename) = newName;

	return new Relation{this, newHeader};
}

Relation* Relation::Rename(const ColumnNames& newColumns)
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

	return new Relation{this, Header(newColumns)};
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
	DEBUG_MSG("Old Header: " << this->header.ToString());
	Header newHeader;
	Tuples newTuples;
	for (auto& i : colsToKeep)
	{
		DEBUG_MSG("colToKeep: " << i);
		newHeader.push_back(this->header.at(i));
	}

	DEBUG_MSG("New Header: " << newHeader.ToString());
	for (Tuple t : tuples)
	{
		Tuple newTuple;
		for (auto& i : colsToKeep)
		{
			newTuple.push_back(t.at(i));
		}
		DEBUG_MSG("newTuple size: " << newTuple.size());
		newTuples.insert(newTuple);
	}
	DEBUG_MSG("newTuples size: " << newTuples.size());
	return new Relation{name, newHeader, newTuples};
}

#ifndef __GNUC__
#pragma region Natural Join
#endif

Relation* Relation::NaturalJoin(Relation* other)
{
	Relation* outputTable = new Relation();

	// set name of output relation
	outputTable->SetName(this->GetName() + " |x| " + other->GetName());

	// calculate header overlap of 'this' and 'other' relations
	/*
		let Header h1 be r1's header
		let Header h2 be r2's header

		initialize overlap (what type should this be? maybe a map or 2 vectors?)
		initialize uniqueCols (what type should this be? maybe a vector or set)

		for index2 = 0 to h2.size():
			found = false

			for index1 = 0 to h1.size():
				if (h1[index1] == h2[index2]):
					found = true
					add index1, index2 to your overlap structure
				end if
			end index1 for loop

			if (not found):
				add index2 to uniqueCols
			end if
		end index2 for loop
	 */
	Header thisHeader = this->GetHeader();
	Header otherHeader = other->GetHeader();

	HeaderOverlap headerOverlap = HeaderOverlap::FindHeaderOverlap(thisHeader, otherHeader);

	// combine headers -- will be the header for 'output'
	outputTable->SetHeader(CombineHeaders(thisHeader, otherHeader, headerOverlap.uniqueColumns));

	// combine tuples -- will be the tuples for
	for (auto rowThis : this->GetTuples())
	{
		for (auto rowOther : other->GetTuples())
		{
			if (IsJoinable(rowThis, rowOther, headerOverlap.valueOverlaps))
			{
				outputTable->insert(CombineTuples(rowThis, rowOther, headerOverlap.uniqueColumns));
			}
		}
	}

	return outputTable;
}

bool Relation::IsJoinable(Tuple& t1, Tuple& t2, const map<Index, Index>& valueOverlaps)
{
	for (auto& index : valueOverlaps)
	{
		if (t1.at(index.first) != t2.at(index.second))
		{
			return false;
		}
	}
	return true;
}

Header Relation::CombineHeaders(const Header& headerThis, Header& headerOther, const set<Index>& uniqueColumns)
{
	Header newHeader(headerThis.GetColumns());
	for (auto& i : uniqueColumns)
	{
		newHeader.push_back(headerOther.at(i));
	}
	return newHeader;
}

Tuple Relation::CombineTuples(Tuple& thisRow, Tuple& otherRow, const set<Index>& uniqueColumns)
{
	Tuple newTuple(thisRow.GetValues());
	for (auto i : uniqueColumns)
	{
		newTuple.push_back(otherRow.at(i));
	}
	return newTuple;
}

#ifndef __GNUC__
#pragma endregion
#endif

pair<Tuples::iterator, bool> Relation::insert(const Tuple& t)
{
	return tuples.insert(t);
}

void Relation::Union(Relation* tableToJoin)
{
	for (Tuple row : tableToJoin->GetTuples())
	{
		if (insert(row).second)
		{
			cout << "  " << row.ToString(tableToJoin->GetHeader()) << endl;
		}
	}
}

#ifndef __GNUC__
#pragma region Getters & Setters
#endif

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

#ifndef __GNUC__
#pragma endregion
#endif

HeaderOverlap HeaderOverlap::FindHeaderOverlap(Header thisHeader, Header otherHeader)
{
	HeaderOverlap newCombo;
	for (Index otherIndex = 0; otherIndex < otherHeader.size(); otherIndex++)
	{
		bool found = false;
		for (Index thisIndex = 0; thisIndex < thisHeader.size(); thisIndex++)
		{
			if (thisHeader.at(thisIndex) == otherHeader.at(otherIndex))
			{
				found = true;
				newCombo.valueOverlaps.insert({thisIndex, otherIndex});
				newCombo.numsInCommon.push_back(otherIndex);

				// TODO: return a struct with num pair and bool? or just pair?
			}
		}
		if (!found)
		{
			newCombo.uniqueColumns.insert(otherIndex);
		}
	}
	return newCombo;
}

HeaderOverlap HeaderOverlap::FindHeaderOverlap(const Predicate& headPredicate, Header joinedTableHeader)
{
	HeaderOverlap newCombo;

	const auto& headParameters = headPredicate.GetParameters();

	map<string, Index> joinedTableMap;
	for (Index iH = 0; iH < joinedTableHeader.size(); iH++)
	{
		joinedTableMap.insert({joinedTableHeader.at(iH), iH});
	}

	for (Index iP = 0; iP < headParameters.size(); iP++)
	{
		const auto& parameter = headParameters.at(iP);
		auto iter = joinedTableMap.find(parameter);
		if (iter != joinedTableMap.end())
		{
			DEBUG_MSG("parameters at " << iP << ": " << string(parameter));
			DEBUG_MSG("map[" << string(parameter) << "]:" << joinedTableMap[parameter]);
			newCombo.numsInCommon.push_back(joinedTableMap[parameter]);
		}
		else
			newCombo.uniqueColumns.insert(joinedTableMap[parameter]);

		// TODO: return a struct with num pair and bool? or just pair?
	}


	return newCombo;
}