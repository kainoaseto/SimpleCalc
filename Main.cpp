/*
 * SimpleCalc
 * Kainoa Seto
 * Simple calculator language Scanner, Parser, and Interpretor using C++/C
 * 11-29-16
 */

#include "pch.h"
#include "CScanner.h"
#include "CParser.h"

int main(int argc, char *argv[])
{
	CScanner* scanner = new CScanner();
    CParser parser(scanner);

	if (argc > 1 && (!scanner->OpenFile(argv[1])))
	{
		cout << "Error: Cannot open input file " << argv[1] << endl;
		exit(1);
	}

    parser.Parse();
}
