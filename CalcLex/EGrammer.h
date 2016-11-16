#ifndef __EGRAMMER_H__
#define __EGRAMMER_H__

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

enum EgrammerTokens {
	EOFSY = 0,
	ADDOP,
	SUBOP,
	MULOP,
	DIVOP,
	LPAREN,
	RPAREN,
	NUMCONST,
	ID,
	READSY,
	WRITESY,
	ASSIGNOP
};





#define YYTEXT_MAX 100
// Global token text buffer
extern char yytext[YYTEXT_MAX];

bool yylexopen(const char filename[]);
void yytextclear();
void yytextappend(int c);
int yylex();

int yyparse();

#endif // __EGRAMMER_H__