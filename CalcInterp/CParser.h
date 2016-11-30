/*
 * Kainoa Seto
 * The Parser and interpreter for the code but since this class mainly holds Parser calls
 * I named it after those. The custom stack defined below allows for data to be moved
 * between the functions in an easier to understand way then passing by variables. However
 * it may be more efficient to eventually implement variable passing and do away with the
 * custom stack.
 * 11-29-16
 */

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
