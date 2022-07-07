#include "Output.h"

ostream& operator << (ostream& out, const Output& self)
{
	out << self.name
		<< Symbols[LEFT_PAREN] << self.size << Symbols[RIGHT_PAREN]
		<< Symbols[COLON] << endl;

	for (auto& s : self.output)
	{
		out << "\t" << self.prefix << s << self.suffix << endl;
	}
	return out;
}

istream& operator >> (istream& in, const Output& self)
{
	return in;
}

