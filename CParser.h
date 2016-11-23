#ifndef __CPARSER_H__
#define __CPARSER_H__

#include "pch.h"
#include "CScanner.h"

class CParser
{
public:
    CParser(CScanner* scanner);
    ~CParser() {};
    void Parse();

private:
    void match(int expectedToken);

    // Recursive grammar calls
    void program();
    void stmt_list();
    void stmt();
    void expr();
    void term_tail();
    void term();
    void factor_tail();
    void factor();

    // Custom 'stack'
    double stack[100];
    int top;
    void stackinit()    { top = 0; }
    double pop()           { return stack[top--]; }
    void push(double v)    { stack[++top] = v; }

    int token;
    CScanner* scanner;
    map<string, double> symbolTable;

};

#endif //__CPARSER_H__
