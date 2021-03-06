/*
 * Kainoa Seto
 * The sourcecode the scanner. Mostly implemented in C code for efficiency it allows for
 * tokens to be processed one at a time while also receiving the token char if neccessary.
 * 11-29-16
 */

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

void CScanner::clear_yytext()
{
	yytextpos = 0;
	yytext[yytextpos] = 0;
}

void CScanner::append_yytext(int c)
{
    // Ignore char
	if (yytextpos >= YYTEXT_MAX - 1)
		return;
	yytext[yytextpos++] = (char)c;
    // Null sentinel at end
	yytext[yytextpos] = 0;
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
        {
			return EOFSY;
		}
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
            bool decimalFound = false;
			while ( ( (c = file_in.get()) >= '0' && c <= '9') || (c == '.') )
            {
                // Ignore all other numbers after a second decimal point is found
                if (c == '.' && decimalFound)
                    return NUMCONST;
                else if (c == '.') {
                    decimalFound = true;
                }

                append_yytext(c);
            }


			file_in.unget();
			return NUMCONST;
		}
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
            // Above we assigned this character but if we are here then we need to make sure its
            // case independent by setting it to be uppercase
            yytext[yytextpos-1] = (char)toupper(c);

			int cc = file_in.get();

			while ((cc >= 'a' && cc <= 'z') || (cc >= 'A' && cc <= 'Z') || (cc == '_'))
            {
				append_yytext(toupper(cc));
				cc = file_in.get();
			}

			if (strcmp(yytext, "READ") == 0)
			{
				return READSY;
			}
			if (strcmp(yytext, "WRITE") == 0)
			{
				return WRITESY;
			}
            file_in.unget();
			return ID;
		}

		// Just return the undefined input
		return c;
	}
	// Should never get here
	return EOFSY;
}

void CScanner::PrintTokens()
{
    int token;
    do {
        token = GetToken();
        cout << "tok = " << setw(2) << setfill('0') << token << " " << TokenNames[token] << " (" << GetTokenChar() << ")" << endl;
    } while ((token) != EOFSY);

    cout << "Number of tokens: " << GetTokenCount() << endl;
}
