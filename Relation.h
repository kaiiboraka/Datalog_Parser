#pragma once
#include "Helper.h"
#include "Tuple.h"
#include <set>
typedef set<Tuple> Tuples;

class Relation
{
private:
	string name;
	Header header;
	Tuples tuples;
public:
	Relation() = default;
	explicit Relation(const string& newName);
	Relation(const Relation* other, const string& instruction = "");
	Relation(const Relation* other, const Header& newHeader);
	Relation(const string& newName, const Header& newHeader, const Tuples& newTuples);

	Relation* Select(unsigned int colIdx, const string& expectedValue);

	Relation* Select(unsigned int col1, unsigned int col2);

	Relation* Rename(unsigned int colToRename, const string& newName);
	Relation* Rename(const ColumnNames& newColumns);

	//pi_{BCD} R
	Relation* Project(const vector<unsigned int>& colsToKeep);

	void AddTuple(Tuple t);
	[[nodiscard]] const string& GetName() const;
	[[nodiscard]] const Header& GetHeader() const;
	[[nodiscard]] const set<Tuple>& GetTuples() const;
	void SetName(const string& name);
	void SetHeader(const Header& header);
	void SetTuples(const set<Tuple>& tuples);
	string ToString();
};
