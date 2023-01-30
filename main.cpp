#include "Token.h"
#include <iostream>
using namespace std;


int main() {
    TokenType tt = VOID_TOKEN;
	string lexeme = "void";
	TokenClass tok1(tt, lexeme);
	cout << tok1 << endl;
    return 0;
}