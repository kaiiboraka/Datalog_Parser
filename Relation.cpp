#include "Relation.h"

const string& Relation::GetName() const
{
	return name;
}

void Relation::SetName(const string& name)
{
	Relation::name = name;
}

const Header& Relation::GetHeader() const
{
	return header;
}

void Relation::SetHeader(const Header& header)
{
	Relation::header = header;
}

const set<Tuple>& Relation::GetTuples() const
{
	return tuples;
}

void Relation::SetTuples(const set<Tuple>& tuples)
{
	Relation::tuples = tuples;
}
