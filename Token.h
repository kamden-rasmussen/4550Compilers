#pragma once

using namespace std;
#include <string>
#include <iostream>
#include "Debug.h"

enum TokenType {
    // Reserved Words:
    VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN, PRINT_TOKEN,
    // Relational Operators:
    LESS_TOKEN, LESS_EQUAL_TOKEN, GREATER_TOKEN, GREATER_EQUAL_TOKEN, EQUAL_TOKEN, NOTEQUAL_TOKEN,
    IF_TOKEN, WHILE_TOKEN, AND_TOKEN, OR_TOKEN, ELSE_TOKEN,
    // Other Operators:
    INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN, TIMES_TOKEN, DIVIDE_TOKEN, EXPONENT_TOKEN,
    // Other Characters:
    SEMICOLON_TOKEN, LEFT_PAREN_TOKEN, RIGHT_PAREN_TOKEN, LEFT_CURLY_TOKEN,
    RIGHT_CURLY_TOKEN,
    // Other Token Types:
    IDENTIFIER_TOKEN, INTEGER_TOKEN, 
    BAD_TOKEN, ENDFILE_TOKEN
};

const string gTokenTypeNames[] = {
    "VOID", "MAIN", "INT", "COUT", "PRINT"
    "LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL", "NOTEQUAL",
    "IF", "WHILE", "AND", "OR", "ELSE",
    "INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", "DIVIDE", "EXPONENT",
    "SEMICOLON", "LEFTPAREN", "RIGHTPAREN", "LEFTCURLY", "RIGHTCURLY",
    "IDENTIFIER", "INTEGER", 
    "BAD", "ENDFILE"
};

class TokenClass
{
private:
	TokenType mType;
	string mLexeme;
public:
	TokenClass();
	TokenClass(TokenType type, const string & lexeme);
	TokenType GetTokenType() const;
	const string &GetTokenTypeName() const;
	string GetLexeme() const;
	void CheckReserved();
	static const string & GetTokenTypeName(TokenType type);
};

ostream & operator<<(ostream & out, const TokenClass & tc);

