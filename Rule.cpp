//
// Created by Brandon on 7/7/2022.
//

#include "Rule.h"

const Predicate& Rule::GetHead() const
{
	return head;
}

void Rule::SetHead(const Predicate& head)
{
	Rule::head = head;
}

const vector<Predicate>& Rule::GetBody() const
{
	return body;
}

void Rule::SetBody(const vector<Predicate>& body)
{
	Rule::body = body;
}
