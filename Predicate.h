#pragma once

#include "Tuple.h"

class Predicate
{
	string name;
	Parameters parameters;

public:
	Predicate() = default;

	Predicate(Parameters& parameters, const string& name = "")
		: name(name), parameters(parameters)
	{}

	[[nodiscard]] const string& GetName() const;
	[[nodiscard]] const Parameters& GetParameters() const;
	[[nodiscard]] Values GetParameterValues() const;
	Tuple GetParametersAsTuple();

	void SetName(const string& newName);
	void SetParameters(const Parameters& newParameters);

	void AddParameter(const Parameter& newParameter);
	void AddParameter(const string& parameterValue);

	[[nodiscard]] string ToString() const;

	Predicate operator=(vector<string>& other)
	{
		Parameters p;
		for (auto& s : other)
		{
			p.push_back(Parameter{s});
		}
		return Predicate{p};
	}

	bool operator==(const string& other)
	{
		return this->name == other;
	}
	bool operator!=(const string& other)
	{
		return this->name != other;
	}
	operator string() const
	{
		return name;
	}

};

