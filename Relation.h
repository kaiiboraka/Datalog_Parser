#pragma once
#include "Helper.h"
#include "Tuple.h"
#include "Predicate.h"
#include <set>
typedef set<Tuple> Tuples;

struct HeaderOverlap
{
	map<Index, Index> valueOverlaps;
	set<Index> uniqueColumns;
	ColumnNums numsInCommon;

	static HeaderOverlap FindHeaderOverlap(Header thisHeader, Header otherHeader);
	static HeaderOverlap FindHeaderOverlap(const Predicate& headPredicate, Header joinedTableHeader);
};

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
	Relation(const string& newName, const Header& newHeader, const Tuples& newTuples = {});

	Relation* Select(Index colIdx, const string& expectedValue);
	Relation* Select(Index col1, Index col2);
	Relation* Rename(Index colToRename, const string& newName);
	Relation* Rename(const ColumnNames& newColumns);
	Relation* Project(const ColumnNums& colsToKeep);

	Relation* NaturalJoin(Relation* other);
	bool IsJoinable (Tuple& t1, Tuple& t2, const map<Index, Index>& valueOverlaps);
	static Header CombineHeaders(const Header& headerThis, Header& headerOther, const set<Index>& uniqueColumns);
	Tuple CombineTuples(Tuple& thisRow, Tuple& otherRow, const set<Index>& uniqueColumns);

	pair<Tuples::iterator, bool> insert(const Tuple& t);
	void Union(Relation* tableToJoin);

	[[nodiscard]] const string& GetName() const;
	[[nodiscard]] const Header& GetHeader() const;
	[[nodiscard]] const set<Tuple>& GetTuples() const;
	void SetName(const string& name);
	void SetHeader(const Header& header);
	void SetTuples(const set<Tuple>& tuples);

	[[nodiscard]] unsigned int size() const;
	[[nodiscard]] bool empty() const;

	[[nodiscard]] string ToString() const;


};
