#ifndef __CGRAMMER_H__
#define __CGRAMMER_H__

#include <vector>
#include "pch.h"


/* Grammer CFG rules
 *
 * program()        -> stmt_list() EOFSY
 * stmt_list()      -> stmt() stmt_list()
 * stmt_list()      -> <epsilon>
 * stmt()           -> ID := expr()
 * stmt()           -> ID := read ID
 * stmt()           -> write expr()
 * expr()           -> term() term_tail()
 * term_tail()      ->  + term() term_tail()
 * term_tail()      ->  - term() term_tail()
 * term()           ->  factor() factor_tail()
 * factor_tail()    ->  * factor() factor_tail()
 * factor_tail()    ->  / factor() factor_tail()
 * factor_tail()    -> <epsilon>
 * factor()         -> ( expr() )
 * factor()         -> ID
 * factor()         -> NUMCONST
 *
 * Where <epsilon> is anything
 * The grammar definitions are located inside the CParser class
 */

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
