#pragma once

#include "Helper.h"

namespace Tokens
{
	enum TokenType
	{
		COMMA,
		PERIOD,
		Q_MARK,
		LEFT_PAREN,
		RIGHT_PAREN,
		COLON,
		COLON_DASH,
		MULTIPLY,
		ADD,
		SCHEMES,
		FACTS,
		RULES,
		QUERIES,
		ID,
		STRING,
		COMMENT,
		UNDEFINED,
		END_OF_FILE,
		TYPE_COUNT
	};

	static const string TokenNames[] =
	{
		"COMMA",
		"PERIOD",
		"Q_MARK",
		"LEFT_PAREN",
		"RIGHT_PAREN",
		"COLON",
		"COLON_DASH",
		"MULTIPLY",
		"ADD",
		"SCHEMES",
		"FACTS",
		"RULES",
		"QUERIES",
		"ID",
		"STRING",
		"COMMENT",
		"UNDEFINED",
		"EOF",
		"TYPE_COUNT"
	};

	static map<TokenType, string> Symbols =
	{
		{COMMA,       ","},
		{PERIOD,      "."},
		{Q_MARK,      "?"},
		{LEFT_PAREN,  "("},
		{RIGHT_PAREN, ")"},
		{COLON,       ":"},
		{COLON_DASH,  ":-"},
		{MULTIPLY,    "*"},
		{ADD,         "+"},
		{SCHEMES,     Helper::ToCapitalized(TokenNames[SCHEMES])},
		{FACTS,       Helper::ToCapitalized(TokenNames[FACTS])},
		{RULES,       Helper::ToCapitalized(TokenNames[RULES])},
		{QUERIES,     Helper::ToCapitalized(TokenNames[QUERIES])},
		{ID,          TokenNames[ID]},
		{STRING,      "'"},
		{COMMENT,     "#"},
		{UNDEFINED,   TokenNames[UNDEFINED]},
		{END_OF_FILE, ""},
		{TYPE_COUNT,  ""},
	};

	static string SpacedToken(TokenType token)
	{
		return string(" " + Symbols[token] + " ");
	}

	class Token
	{
		TokenType type;
		string value;
		unsigned int line;
	public:

		Token()
		{
			type = UNDEFINED;
			value = Symbols[UNDEFINED];
			line = 0;
		}
		Token(const string& newValue, const TokenType& newType = UNDEFINED, const unsigned int& newLine = 0)
				: type(newType), value(newValue), line(newLine)
		{}

		const string& GetValue() const
		{
			return value;
		}

		TokenType GetType() const
		{
			return type;
		}

		string ToString() const
		{
			ostringstream oss;
			oss << "(" << TokenNames[type] << "," << "\"" << value << "\"" << "," << line << ")";
			return oss.str();
		}
	};

}