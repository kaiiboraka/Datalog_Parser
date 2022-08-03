#pragma once

#include "Predicate.h"

class Rule
{
	Predicate head;
	vector<Predicate> body;
	Index ID;

public:
	Rule() = default;
	Rule (const string& other)
		: head(other) {}
	Rule(Predicate& head, vector<Predicate>& body)
		: head(head), body(body) {}

	[[nodiscard]] const Predicate& GetHead() const;
	[[nodiscard]] const vector<Predicate>& GetBody() const;
	Index GetID() const;
	void SetHead(const Predicate& newHead);
	void SetBody(const vector<Predicate>& newBody);
	void SetID(Index id);

	void AddPredicate(const Predicate& predicate);

	[[nodiscard]] string ToString() const;
	Predicate& at(Index i);

	bool operator<(const Rule& other) const
	{
		return ID < other.ID;
	}
	bool operator>(const Rule& other) const
	{
		return ID > other.ID;
	}
};
