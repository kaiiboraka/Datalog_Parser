#include "Output.h"

ostream& operator << (ostream& out, const Output& self)
{
	out << self.name
		<< Symbols[LEFT_PAREN] << self.size << Symbols[RIGHT_PAREN]
		<< Symbols[COLON] << endl;

	for (auto& string : self.output)
	{
		out << "  " << self.prefix << string << self.suffix << endl;
	}
	return out;
}

istream& operator >> (istream& in, const Output& self)
{
	return in;
}

