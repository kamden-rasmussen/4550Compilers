#pragma once
#include "Scanner.h"
#include "Symbol.h"
#include "Debug.h"
#include "Node.h"


class ParserClass {

    public:
        ParserClass(ScannerClass *scanner, SymbolTableClass *symbolTable);
        ~ParserClass();
        StartNode* Start();
        ExpressionNode* Expression();
        ExpressionNode* Relational();
        ExpressionNode* PlusMinus();
        ExpressionNode* TimesDivide();
        ExpressionNode* Factor();
        TokenClass Match(TokenType expected);
        ProgramNode* Program();
        BlockNode* Block();
        StatementGroupNode* StatementGroup();
        DeclarationStatementNode* DeclarationStatement();
        AssignmentStatementNode* AssignmentStatement();
        CoutStatementNode* CoutStatement();
        IdentifierNode* Identifier();
        IntegerNode* Integer();


    private:
        ScannerClass *mScanner;
        SymbolTableClass *mSymbolTable;

};