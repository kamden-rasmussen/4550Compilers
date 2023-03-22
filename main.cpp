#include "Scanner.h"
#include "Token.h"
#include "Symbol.h"
#include "Node.h"
#include "Parser.h"

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
        TokenClass token = scanner.GetNextToken();
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

void testNodes(){
    SymbolTableClass symbols;
    StatementGroupNode* sgn = new StatementGroupNode () ;

    IdentifierNode* id1 = new IdentifierNode ("sum", &symbols);
    DeclarationStatementNode* dsn = new DeclarationStatementNode (id1);
    sgn->AddStatement (dsn);
    IdentifierNode* id2 = new IdentifierNode("sum", &symbols);
    IntegerNode* in1 = new IntegerNode (35) ;
    IntegerNode* in2 = new IntegerNode (400);
    PlusNode* p1 = new PlusNode(in1, in2);
    AssignmentStatementNode* asn = new AssignmentStatementNode (id2, p1);
    sgn->AddStatement(asn);
    IdentifierNode* id3 = new IdentifierNode ("sum", &symbols);
    CoutStatementNode* csn = new CoutStatementNode (id3);
    sgn->AddStatement(csn);
    
    BlockNode* b = new BlockNode (sgn);

    ProgramNode* pn = new ProgramNode (b) ;

    StartNode*s = new StartNode (pn) ;

    delete s;
}

void testParser(){
    
    ScannerClass scanner("test2.c");
    SymbolTableClass symbolTable;
    ParserClass parser(&scanner, &symbolTable);
    parser.Start();
}

void testParserWithOutput(){
    ScannerClass scanner("test2.c");
    SymbolTableClass symbolTable;
    ParserClass parser(&scanner, &symbolTable);
    StartNode* start = parser.Start();
    MSG("PARSER DONE");
    delete start;
}

void testInterpreter(){
    ScannerClass scanner("test2.c");
    SymbolTableClass symbolTable;
    ParserClass parser(&scanner, &symbolTable);
    StartNode* start = parser.Start();
    start->Interpret();
    MSG("PARSER DONE");
    delete start;
}

int main(){
    // testToken();
    // testScanner();
    // testSymbol();
    // testNodes();
    // testParser();
    // testParserWithOutput();
    testInterpreter();
    return 0;
}
