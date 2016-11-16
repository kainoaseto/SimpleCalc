#include "pch.h"
#include "CScanner.h"

CScanner::CScanner()
{
	yytextpos = 0;
	tokens = 0;
}

bool CScanner::OpenFile(const char* filename)
{
	file_in.open(filename, ios_base::in);
	return file_in.is_open();
}

char* CScanner::GetTokenChar()
{
    return yytext;
}

unsigned int CScanner::GetTokenCount()
{
    return tokens;
}

int CScanner::GetToken()
{
	int c;
	for(;;)
	{
		clear_yytext();

		// Skip whitespace
		while ((c = file_in.get()) == ' ' || c == '\t' || c == '\n')
			continue;

		if (c == '/' && file_in.peek() == '*')
		{
			while ( (c = file_in.get()) )
            {
				if ((c == '*' && file_in.peek() == '/') || c == '\n')
                {
					file_in.get();
					break;
				}
			}
			continue;
		}

		if (c == EOF)
            return EOFSY;

		append_yytext(c);
        tokens++;

		if (c == ':' && file_in.peek() == '=')
        {
			append_yytext(file_in.get());
			return ASSIGNOP;
		}
		if (c == '+') return ADDOP;
		if (c == '-') return SUBOP;
		if (c == '*') return MULOP;
		if (c == '/') return DIVOP;
		if (c == '(') return LPAREN;
		if (c == ')') return RPAREN;
		if (c >= '0' && c <= '9' )
		{
			// If its a number or contains a decimal point with numbers around it
			// it is a number constant
			while ( ( (c = file_in.get()) >= '0' && c <= '9') || (c == '.') )
				append_yytext(c);

			file_in.unget();
			return NUMCONST;
		}
		// If it doesnt contain any symbols or numbers then it is at least an ID
		// It could also be one of the keywords though so check for that
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			int cc = file_in.get();

			while ((cc >= 'a' && cc <= 'z') || (cc >= 'A' && cc <= 'Z'))
            {
				append_yytext(cc);
				cc = file_in.get();
			}

			if (strcmp(yytext, "read") == 0)
				return READSY;
			if (strcmp(yytext, "write") == 0)
				return WRITESY;

            file_in.unget();
			return ID;
		}


		// Just return the undefined input
		return c;
	}
	// Should never get here
	return EOFSY;
}

void CScanner::clear_yytext()
{
	yytextpos = 0;
	yytext[yytextpos] = 0;
}

void CScanner::append_yytext(int c)
{
	// If out of bounds ignore char
	if (yytextpos >= YYTEXT_MAX - 1)
		return; 
	yytext[yytextpos++] = (char)c;
	// null sentinel at end
	yytext[yytextpos] = 0; 
}