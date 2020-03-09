#include <iostream>
#include <string>

using namespace std;

ifstream fin ("lexer.in");
ofstream fout ("lexer.out");

// The lexer returns tokens [0-255] if it is an unknown character, otherwise one
// of these for known things.
enum Token {
	tok_eof = -1,

	// commands
	tok_print = -2,
	tok_add = -3,
	tok_equal = -4,
	tok_diff = -5,
	tok_mutliply = -6,
	tok_division = -7,
	tok_mod = -8,

	// primary
	tok_identifier = -9,
	tok_number = -10,
	tok_end = -11,
};

static string IdentifierStr; // Filled in if tok_identifier
static double NumVal;             // Filled in if tok_number

/// gettok - Return the next token from standard input.
static int gettok() {
	static int LastChar = ' ';

	// Skip any whitespace.
	while (isspace(LastChar))
	    LastChar = getchar();

	if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
		IdentifierStr = LastChar;
		while (isalnum((LastChar = getchar())))
			IdentifierStr += LastChar;

		if (IdentifierStr == "print")
			return tok_print;
		if (IdentifierStr == "+")
			return tok_add;
		if (IdentifierStr == "=")
			return tok_equal;
		if (IdentifierStr == "-")
			return tok_diff;
		if (IdentifierStr == "*")
			return tok_mutliply;
		if (IdentifierStr == "/")
			return tok_division;
		if (IdentifierStr == "%")
			return tok_mod;
		if (IdentifierStr == "")
			return tok_end;
		return tok_identifier;
	}

	if (isdigit(LastChar) || LastChar == '.') {   // Number: [0-9.]+
		string NumStr;
		do {
			NumStr += LastChar;
			LastChar = getchar();
			} while (isdigit(LastChar) || LastChar == '.');

		NumVal = strtod(NumStr.c_str(), 0);
		return tok_number;
	}

	if (LastChar == '#') {
		// Comment until end of line.
		do
			LastChar = getchar();
			while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

		if (LastChar != EOF)
			return gettok();
	}

	  // Check for end of file.  Don't eat the EOF.
	  if (LastChar == EOF)
	    return tok_eof;

	  // Otherwise, just return the character as its ascii value.
	  int ThisChar = LastChar;
	  LastChar = getchar();
	  return ThisChar;
}

int main()
{
	/* code */
	return 0;
}