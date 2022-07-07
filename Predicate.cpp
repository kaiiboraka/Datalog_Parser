//
// Created by Brandon on 7/7/2022.
//

#include "Predicate.h"

const vector<Parameter>& Predicate::GetParameters() const
{
	return parameters;
}

void Predicate::SetParameters(const vector<Parameter>& parameters)
{
	Predicate::parameters = parameters;
}

const string& Predicate::GetName() const
{
	return name;
}

void Predicate::SetName(const string& name)
{
	Predicate::name = name;
}

void Predicate::AddParameter(const string& parameterValue)
{
	parameters.emplace_back(parameterValue);
}

string Predicate::ToString()
{
	string sep;
	stringstream out;
	out << name << "(";
	for (const Parameter& currParam : parameters) {
		out << sep << currParam.ToString();
		sep = ",";
	}
	out << ")";
	return out.str();
}
