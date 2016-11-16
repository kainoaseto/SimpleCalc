#include "pch.h"
#include "CGrammer.h"
#include "CScanner.h"

/*
	While using mixed C++/C is less efficient than pure C code or pure well maintained C++ code...
	It is more readable and easier to understand in this program's context which is meant to be
	an example more than anything.
*/

int main(int argc, char *argv[])
{
	CScanner scanner;

	if (argc > 1 && (!scanner.OpenFile(argv[1])))
	{
		cout << "Error: Cannot open input file " << argv[1] << endl;
		exit(1);
	}

	int token;
	do {
		token = scanner.GetToken();
		cout << "tok = " << setw(2) << setfill('0') << token << " " << TokenNames[token] << " (" << scanner.GetTokenChar() << ")" << endl;
	} while ((token) != EOFSY);

	cout << "Number of tokens: " << scanner.GetTokenCount() << endl;
}
