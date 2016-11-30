/*
 * Kainoa Seto
 * The recursive descent parser and interpreter as certain tokens are reached. This makes
 * direct calls to the Scanner instance that is passed into the constructor and then gets
 * all tokens from the src file and decides what to do when it receives certain tokens based
 * on the grammer defined in CGrammer.h
 * 11-29-16
 */
#include "CParser.h"

CParser::CParser(CScanner* scanner)
{
    // Initialize our stack, really its just a well navigated array
    stackinit();
    top = 0;
    this->scanner = scanner;
}

void CParser::Parse()
{
    program();
}

void CParser::match(int expectedToken)
{
    if(token == expectedToken)
    {
        if(token != EOFSY)
            token = scanner->GetToken();
    }
    else
    {
        // Exit on any unexpected token or syntax errors, don't just skip over them
        cout << "Token " << TokenNames[expectedToken] << "(" << expectedToken << ")"
             << " expected, but instead encountered "
             << scanner->GetTokenChar() << endl;
        exit(1);
    }
}

void CParser::program()
{
    token = scanner->GetToken();

    stmt_list();
    match(EOFSY);
}

void CParser::stmt_list()
{
    if(token == ID || token == READSY || token == WRITESY)
    {
        stmt();
        stmt_list();
    }
}

void CParser::stmt()
{
    if(token == ID)
    {
        string currentId = scanner->GetTokenChar();
        match(ID);
        match(ASSIGNOP);
        expr();
        symbolTable[currentId] = pop();
        cout << "Assign: " << currentId << " = " << symbolTable[currentId] << endl;
    }
    if(token == READSY)
    {
        double readValue = 0.0;
        match(READSY);
        cout << "Read: Enter value for " << scanner->GetTokenChar() << "> ";
        cin >> readValue;
        symbolTable[scanner->GetTokenChar()] = readValue;
        match(ID);
    }
    if(token == WRITESY)
    {
        match(WRITESY);
        expr();
        cout << "Write: " << pop() << endl;
    }

}

void CParser::expr()
{
    term();
    term_tail();
}

void CParser::term_tail()
{
    if (token == ADDOP)
    {
        match(ADDOP);
        term();
        double firstValue = pop();
        double secondValue = pop();
        push(firstValue+secondValue);
        term_tail();
    }
    else if(token == SUBOP)
    {
        match(SUBOP);
        term();
        double firstValue = pop();
        double secondValue = pop();
        push(secondValue-firstValue);
        term_tail();
    }
}

void CParser::term()
{
    factor();
    factor_tail();
}

void CParser::factor_tail()
{
    if(token == MULOP)
    {
        match(MULOP);
        factor();
        double firstValue = pop();
        double secondValue = pop();
        push(firstValue*secondValue);
        factor_tail();
    }
    else if(token == DIVOP)
    {
        match(DIVOP);
        factor();
        double firstValue = pop();
        double secondValue = pop();
        push(secondValue/firstValue);
        factor_tail();
    }
}

void CParser::factor()
{
    // Handle ( expresion )
    if(token == LPAREN)
    {
        match(LPAREN);
        expr();
        match(RPAREN);
    }
    // Handle an ID/Variable name
    else if(token == ID)
    {
        if(symbolTable.count(scanner->GetTokenChar()) == 0)
        {
            cout << "ERROR couldn't find token value in symbol table!" << endl;
            exit(1);
        }
        push(symbolTable[scanner->GetTokenChar()]);
        match(ID);
    }
    // Handle any constants/numbers
    else if(token == NUMCONST)
    {
        push(atof(scanner->GetTokenChar()));
        match(NUMCONST);

    }
}
