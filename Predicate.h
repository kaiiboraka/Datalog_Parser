#pragma once

#include "Parameter.h"

class Predicate
{
	vector<Parameter> parameters;
	string name;
public:
	Predicate() = default;
	Predicate(vector<Parameter>& parameters, const string& name)
		: parameters(parameters), name(name) {}
	[[nodiscard]] const vector<Parameter>& GetParameters() const;
	void SetParameters(const vector<Parameter>& parameters);
	[[nodiscard]] const string& GetName() const;
	void SetName(const string& name);

	void AddParameter(const string& parameterValue);
	string ToString();
};