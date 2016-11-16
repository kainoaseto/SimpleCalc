#include "EGrammer.h"

// Global token text buffer
char yytext[YYTEXT_MAX];
static int yytextpos = 0;

// Lex input file stream
ifstream fin;
bool yylexopen(const char filename[])
{
	fin.open(filename, ios_base::in);
	return fin.is_open();
}

void yytextclear()
{
	yytextpos = 0;
	yytext[yytextpos] = 0;
}

void yytextappend(int c)
{
	if (yytextpos >= YYTEXT_MAX - 1)
		return; //ignore char
	yytext[yytextpos++] = (char)c;
	yytext[yytextpos] = 0; // null sentinel at end
}

int yylex() {
	int c;

	while (1) {
		yytextclear();

		// Skip whitespace
		while ((c = fin.get()) == ' ' || c == '\t' || c == '\n')
			continue;

		if (c == '/' && fin.peek() == '*')
		{
			while (c = fin.get()) {
				if ((c == '*' && fin.peek() == '/') || c == '\n') {
					fin.get();
					break;
				}
			}
			continue;
		}

		if (c == EOF) {
			return EOFSY;
		}

		yytextappend(c);

		if (c == ':' && fin.peek() == '=') {
			yytextappend(fin.get());
			return ASSIGNOP;
		}
		if (c == '+') {
			return ADDOP;
		}
		if (c == '-') {
			return SUBOP;
		}
		if (c == '*') {
			return MULOP;
		}
		if (c == '/') {
			return DIVOP;
		}
		if (c == '(') {
			return LPAREN;
		}
		if (c == ')') {
			return RPAREN;
		}
		if (c >= '0' && c <= '9' )
		{
			while ((c = fin.get()) >= '0' && c <= '9' || c == '.')
				yytextappend(c);

			fin.unget();
			return NUMCONST;
		}
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			int cc = fin.get();

			while ((cc >= 'a' && cc <= 'z') || (cc >= 'A' && cc <= 'Z')) {
				yytextappend(cc);
				cc = fin.get();
			}

			if (_stricmp(yytext, "read") == 0)
			{
				return READSY;
			}
			if (_stricmp(yytext, "write") == 0)
			{
				return WRITESY;
			}

			return ID;
		}

		
		// IGNORE UNDEFINED INPUT
		return c;
	}
	// SHould never get here
	return EOFSY;
}