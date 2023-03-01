#include "Parser.h"

ParserClass::ParserClass(ScannerClass *scanner, SymbolTableClass *symbolTable) {
    this->mScanner = scanner;
    this->mSymbolTable = symbolTable;
}

ParserClass::~ParserClass() {

}

// <Start> → <Program> ENDFILE
// <Program> → VOID MAIN LPAREN RPAREN <Block>
// <Block> → LCURLY <StatementGroup> RCURLY
// <StatementGroup> → {empty} 
// <StatementGroup> → <DeclarationStatement> <StatementGroup>
// <StatementGroup> → <AssignmentStatement> <StatementGroup>
// <StatementGroup> → <CoutStatement> <StatementGroup>
// <StatementGroup> → <Block> <StatementGroup>
// <DeclarationStatement> → INT <Identifier> SEMICOLON
// <AssignmentStatement> → <Identifier>ASSIGNMENT<Expression> SEMICOLON 
// <CoutStatement> → COUT INSERTION <Expression> SEMICOLON 

void ParserClass::Start(){
    Program();
    Match(ENDFILE_TOKEN);
}

void ParserClass::Program() {
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LEFT_PAREN_TOKEN);
    Match(RIGHT_PAREN_TOKEN);
    Block();
}

void ParserClass::Block() {
    Match(LEFT_CURLY_TOKEN);
    StatementGroup();
    Match(RIGHT_CURLY_TOKEN);
}

void ParserClass::StatementGroup() {
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == INT_TOKEN)
    {
        DeclarationStatement();
        StatementGroup();
    }
    else if(tt == IDENTIFIER_TOKEN)
    {
        AssignmentStatement();
        StatementGroup();
    }
    else if(tt == COUT_TOKEN)
    {
        CoutStatement();
        StatementGroup();
    }
    else if(tt == LEFT_CURLY_TOKEN)
    {
        Block();
        StatementGroup();
    }
    else
    {
        return;
    }
}

void ParserClass::DeclarationStatement() {
    Match(INT_TOKEN);
    Match(IDENTIFIER_TOKEN);
    Match(SEMICOLON_TOKEN);
}

void ParserClass::AssignmentStatement() {
    Match(IDENTIFIER_TOKEN);
    Match(ASSIGNMENT_TOKEN);
    Expression();
    Match(SEMICOLON_TOKEN);
}

void ParserClass::CoutStatement() {
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);
    Expression();
    Match(SEMICOLON_TOKEN);
}

void ParserClass::Expression() {
    Relational();
}

void ParserClass::Relational() {
	PlusMinus();

	// Handle the optional tail:
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if(tt == LESS_TOKEN)
	{
		Match(tt);
		PlusMinus();
	}
	else if(tt == LESS_EQUAL_TOKEN)
	{
		Match(tt);
		PlusMinus();
	}
	else if(tt == GREATER_TOKEN)
	{
		Match(tt);
		PlusMinus();
	}
	else if(tt == GREATER_EQUAL_TOKEN)
	{
		Match(tt);
		PlusMinus();
	}
	else if(tt == EQUAL_TOKEN)
	{
		Match(tt);
		PlusMinus();
	}
	else if(tt == NOTEQUAL_TOKEN)
	{
		Match(tt);
		PlusMinus();
	}
	else
	{
		return;
	}
}

void ParserClass::PlusMinus() {
    TimesDivide();

    // Handle the optional tail:
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == PLUS_TOKEN)
    {
        Match(tt);
        TimesDivide();
    }
    else if(tt == MINUS_TOKEN)
    {
        Match(tt);
        TimesDivide();
    }
    else
    {
        return;
    }
}

void ParserClass::TimesDivide() {
    Factor();

    // Handle the optional tail:
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == TIMES_TOKEN)
    {
        Match(tt);
        Factor();
    }
    else if(tt == DIVIDE_TOKEN)
    {
        Match(tt);
        Factor();
    }
    else
    {
        return;
    }
}

void ParserClass::Factor() {
    TokenClass tc = mScanner->PeekNextToken();
    TokenType tt = tc.GetTokenType();
    if(tt == IDENTIFIER_TOKEN)
    {
        Match(tt);
    }
    else if(tt == INTEGER_TOKEN)
    {
        Match(tt);
    }
    else if(tt == LEFT_PAREN_TOKEN)
    {
        Match(tt);
        Match(RIGHT_PAREN_TOKEN);
    }
    else
    {
        std::cout << "Error: Expected IDENTIFIER_TOKEN, INTEGER_TOKEN, or LPAREN_TOKEN, but got " << tt << std::endl;
        exit(EXIT_FAILURE);
    }
}

void ParserClass::Match(TokenType expectedType) {
    TokenClass tc = mScanner->GetNextToken();
    TokenType tt = tc.GetTokenType();
    if(tt != expectedType)
    {
        std::cout << "Error: Expected " << expectedType << ", but got " << tt << std::endl;
        exit(EXIT_FAILURE);
    }

}





