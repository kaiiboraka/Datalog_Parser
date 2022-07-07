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
	void SetHead(const Predicate& head);
	[[nodiscard]] const vector<Predicate>& GetBody() const;
	void SetBody(const vector<Predicate>& body);
};
