#include "pch.h"
#include "CGrammer.h"
#include "CScanner.h"

int main(int argc, char *argv[])
{
	CScanner scanner;

	if (argc > 1 && (!scanner.OpenFile(argv[1])))
	{
		cout << "Error: Cannot open input file " << argv[1] << endl;
		exit(1);
	}

	int token;
	while ((token = scanner.GetToken()) != EOFSY)
	{
		cout << "tok = " << setw(2) << setfill('0')  << token << " " << TokenNames[token] <<  " (" << scanner.GetTokenChar() << ")" << endl;
	}

	cout << "tok = " << setw(2) << setfill('0') << token << " " << TokenNames[token] << " (" << scanner.GetTokenChar() << ")" << endl;

	cout << "Number of tokens: " << scanner.GetTokenCount() << endl;
}
