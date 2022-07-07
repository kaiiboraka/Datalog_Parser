//
// Created by Brandon on 7/7/2022.
//

#include "Parameter.h"

const string& Parameter::ToString() const
{
	return value;
}

void Parameter::SetValue(const string& value)
{
	Parameter::value = value;
}

