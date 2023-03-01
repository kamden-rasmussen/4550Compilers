#pragma once
#include "Scanner.h"
#include "Symbol.h"
#include "Debug.h"


class ParserClass {

    public:
        ParserClass(ScannerClass *scanner, SymbolTableClass *symbolTable);
        ~ParserClass();
        void Start();
        void Expression();
        void Relational();
        void PlusMinus();
        void TimesDivide();
        void Factor();
        void Match(TokenType expected);
        void Program();
        void Block();
        void StatementGroup();
        void DeclarationStatement();
        void AssignmentStatement();
        void CoutStatement();


    private:
        ScannerClass *mScanner;
        SymbolTableClass *mSymbolTable;

};