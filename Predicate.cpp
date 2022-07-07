#include "Predicate.h"

const string& Predicate::GetName() const
{
	return name;
}

const vector<Parameter>& Predicate::GetParameters() const
{
	return parameters;
}

void Predicate::SetName(const string& newName)
{
	name = newName;
}

void Predicate::SetParameters(const vector<Parameter>& newParameters)
{
	parameters = newParameters;
}

void Predicate::AddParameter(const Parameter& newParameter)
{
	parameters.push_back(newParameter);
}

void Predicate::AddParameter(const string& parameterValue)
{
	parameters.emplace_back(parameterValue);
}

string Predicate::ToString() const
{
	string sep;
	stringstream out;
	out << name << Symbols[LEFT_PAREN];
	for (const Parameter& currParam : parameters)
	{
		out << sep << currParam.ToString();
		sep = Symbols[COMMA];
	}
	out << Symbols[RIGHT_PAREN];
	return out.str();
}
