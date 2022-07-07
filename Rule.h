#pragma once

#include "Predicate.h"

class Rule
{
	Predicate head;
	vector<Predicate> body;

public:
	Rule() = default;
	Rule(Predicate& head, vector<Predicate>& body)
		: head(head), body(body) {}

	[[nodiscard]] const Predicate& GetHead() const;
	[[nodiscard]] const vector<Predicate>& GetBody() const;
	void SetHead(const Predicate& newHead);
	void SetBody(const vector<Predicate>& newBody);

	void AddPredicate(const Predicate& predicate);

	[[nodiscard]] string ToString() const;
};
