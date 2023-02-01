#include "Scanner.h"
#include "Token.h"

void testToken()
{
    TokenType tt = VOID_TOKEN;
    string lexeme = "void";
    TokenClass token1(tt, lexeme);
    cout << token1 << endl;
}

void testScanner(){
    
    ScannerClass scanner("test.c");
    TokenType tokenType;
    do {
        TokenClass token = scanner.getNextToken();
        cout << scanner.getLineNumber() << " " << token << endl;
        tokenType = token.GetTokenType();
    } while (tokenType != ENDFILE_TOKEN);
}

int main()
{
    testScanner();
    return 0;
}
