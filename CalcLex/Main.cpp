#include "EGrammer.h"

int main(int argc, char *argv[]) 
{
	char* EGrammerTokenNames[] = {
		"EOFSY",
		"ADDOP",
		"SUBOP",
		"MULOP",
		"DIVOP",
		"LPAREN",
		"RPAREN",
		"NUMCONST",
		"ID",
		"READSY",
		"WRITESY",
		"ASSIGNOP"
	};
	int tokens = 1;

	if (argc > 1 && (!yylexopen(argv[1])))
	{
		cout << "Error: Cannot open input file " << argv[1] << endl;
		exit(1);
	}

	int token;
	while ((token = yylex()) != EOFSY)
	{
		tokens++;
		cout << "tok = " << setw(2) << setfill('0')  << token << " " << EGrammerTokenNames[token] <<  " (" << yytext << ")" << endl;
	}

	cout << "tok = " << setw(2) << setfill('0') << token << " " << EGrammerTokenNames[token] << " (" << yytext << ")" << endl;

	cout << "Number of tokens: " << tokens << endl;
}