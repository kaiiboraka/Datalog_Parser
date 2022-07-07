#pragma once

#include "Parameter.h"

class Predicate
{
	string name;
	vector<Parameter> parameters;

public:
	Predicate() = default;
	Predicate(vector<Parameter>& parameters, const string& name)
		: name(name), parameters(parameters){}

	[[nodiscard]] const string& GetName() const;
	[[nodiscard]] const vector<Parameter>& GetParameters() const;

	void SetName(const string& newName);
	void SetParameters(const vector<Parameter>& newParameters);

	void AddParameter(const Parameter& newParameter);
	void AddParameter(const string& parameterValue);

	[[nodiscard]] string ToString() const;
};