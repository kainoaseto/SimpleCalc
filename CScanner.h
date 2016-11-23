#ifndef __CSCANNER_H_
#define __CSCANNER_H_

#include "pch.h"
#include "CGrammer.h"

#define YYTEXT_MAX 100

class CScanner
{

public:
    CScanner();
    ~CScanner() {}

    bool OpenFile(const char* filename);
    int GetToken();
    char* GetTokenChar();
    unsigned int GetTokenCount();

    void PrintTokens();

private:
    unsigned int tokens;
    char yytext[YYTEXT_MAX];
    int yytextpos;

    ifstream file_in;

    void clear_yytext();
    void append_yytext(int token_char);


};

#endif // __CSCANNER_H_
