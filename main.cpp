#include "Scanner.h"
#include "Token.h"
#include "Symbol.h"

void testToken(){
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

void testSymbol(){
    SymbolTableClass symbolTable;
    symbolTable.AddEntry("a");
    symbolTable.AddEntry("b");
    symbolTable.AddEntry("c");
    symbolTable.AddEntry("d");
    symbolTable.AddEntry("e");

    symbolTable.SetValue("a", 1);
    symbolTable.SetValue("b", 2);
    symbolTable.SetValue("c", 3);

    cout << "getValue a " << symbolTable.GetValue("a") << endl;
    cout << "getValue b " << symbolTable.GetValue("b") << endl;

    cout << "getIndex c " <<  symbolTable.GetIndex("c") << endl;

    cout << "getCount " <<  symbolTable.GetCount() << endl;

    cout << "exists z " <<  symbolTable.Exists("z") << endl;
    symbolTable.AddEntry("a");
    cout << "exists a " <<  symbolTable.Exists("a") << endl;

}

int main(){
    // testToken();
    // testScanner();
    testSymbol();
    return 0;
}
