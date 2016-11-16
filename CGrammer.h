#ifndef __CGRAMMER_H__
#define __CGRAMMER_H__

#include <vector>
#include "pch.h"


enum TokenSyms
{
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

static const char* TokenNames[] =
        {
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


#endif // __CGRAMMER_H__
