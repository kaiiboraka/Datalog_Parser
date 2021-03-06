//
// Created by Brandon on 7/7/2022.
//

#include "Rule.h"


const Predicate& Rule::GetHead() const
{
	return head;
}

const vector<Predicate>& Rule::GetBody() const
{
	return body;
}

Index Rule::GetID() const
{
	return ID;
}

void Rule::SetHead(const Predicate& newHead)
{
	head = newHead;
}

void Rule::SetBody(const vector<Predicate>& newBody)
{
	body = newBody;
}

void Rule::SetID(Index id)
{
	ID = id;
}

void Rule::AddPredicate(const Predicate& predicate)
{
	body.push_back(predicate);
}

string Rule::ToString() const
{
	string sep;
	stringstream out;
	out << head.ToString() << Token::SpacedToken(COLON_DASH);
	for(auto& p : body)
	{
		out << sep << p.ToString();
		sep = Symbols[COMMA];
	}
	return out.str();
}

Predicate& Rule::at(Index i)
{
	return body.at(i);
}
