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

StartNode* ParserClass::Start(){
    MSG("START");
    ProgramNode* pn = Program();
    StartNode* sn = new StartNode(pn); // order seems backwards
    Match(ENDFILE_TOKEN);
    MSG("END");
    return sn;
}

ProgramNode* ParserClass::Program() {
    MSG("Program Starting NOW");
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LEFT_PAREN_TOKEN);
    Match(RIGHT_PAREN_TOKEN);
    BlockNode* bn = Block();
    ProgramNode* pn = new ProgramNode(bn);
    MSG("Program Closing")
    return pn;
}

BlockNode* ParserClass::Block() {
    MSG("Block Starting");
    Match(LEFT_CURLY_TOKEN);
    StatementGroupNode* sgn = StatementGroup();
    Match(RIGHT_CURLY_TOKEN);
    BlockNode* bn = new BlockNode(sgn);
    MSG("Block Closing")
    return bn;
}

StatementGroupNode* ParserClass::StatementGroup() {
    MSG("StatementGroup Starting");
    StatementGroupNode* sgn = new StatementGroupNode();
    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == INT_TOKEN)
        {
            DeclarationStatementNode* dsn = DeclarationStatement();
            sgn->AddStatement(dsn);
        }
        else if(tt == IDENTIFIER_TOKEN)
        {
            AssignmentStatementNode* asn = AssignmentStatement();
            sgn->AddStatement(asn);
        }
        else if(tt == COUT_TOKEN)
        {
            CoutStatementNode* csn = CoutStatement();
            sgn->AddStatement(csn);
        }
        else if(tt == LEFT_CURLY_TOKEN)
        {
            BlockNode* bn = Block();
            sgn->AddStatement(bn);
        }
        else
        {
            MSG("StatementGroup Ending")
            return sgn;
        }
    }
}

DeclarationStatementNode* ParserClass::DeclarationStatement() {
    MSG("DeclarationStatement Starting")
    Match(INT_TOKEN);
    IdentifierNode* in = Identifier();
    Match(SEMICOLON_TOKEN);
    MSG("DeclarationStatement Ending")
    DeclarationStatementNode* dsn = new DeclarationStatementNode(in);
    return dsn;
}

AssignmentStatementNode* ParserClass::AssignmentStatement() {
    MSG("AssignmentStatement Starting")
    IdentifierNode* in = Identifier();
    Match(ASSIGNMENT_TOKEN);
    ExpressionNode* en = Expression();
    Match(SEMICOLON_TOKEN);
    MSG("AssignmentStatement Ending")
    AssignmentStatementNode* asn = new AssignmentStatementNode(in, en);
    return asn;
}

CoutStatementNode* ParserClass::CoutStatement() {
    MSG("Starting CoutStatement")
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);
    ExpressionNode* en = Expression();
    Match(SEMICOLON_TOKEN);
    MSG("Ending CoutStatement")
    CoutStatementNode* csn = new CoutStatementNode(en);
    return csn;
}

ExpressionNode* ParserClass::Expression() {
    MSG("Starting Expression")
    ExpressionNode* en = Relational();
    MSG("Ending Expression")
    return en;
}

ExpressionNode* ParserClass::Relational() {
    MSG("Starting Relational")

    ExpressionNode* current = PlusMinus();
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if(tt == LESS_TOKEN)
	{
		Match(tt);
        current = new LessNode(current, PlusMinus());
	}
	else if(tt == LESS_EQUAL_TOKEN)
	{
		Match(tt);
		current = new LessEqualNode(current, PlusMinus());
	}
	else if(tt == GREATER_TOKEN)
	{
		Match(tt);
		current = new GreaterNode(current, PlusMinus());
	}
	else if(tt == GREATER_EQUAL_TOKEN)
	{
		Match(tt);
		current = new GreaterEqualNode(current, PlusMinus());
	}
	else if(tt == EQUAL_TOKEN)
	{
		Match(tt);
		current = new EqualNode(current, PlusMinus());
	}
	else if(tt == NOTEQUAL_TOKEN)
	{
		Match(tt);
		current = new NotEqualNode(current, PlusMinus());
	}
    MSG("Ending Relational")
	return current;
}

ExpressionNode* ParserClass::PlusMinus() {
    
    ExpressionNode* current = TimesDivide();
    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == PLUS_TOKEN) {
            Match(tt);
            current = new PlusNode(current, TimesDivide());
        }
        else if(tt == MINUS_TOKEN) {
            Match(tt);
            current = new MinusNode(current, TimesDivide());
        }
        else {
            return current;
        }
    }
}

ExpressionNode* ParserClass::TimesDivide() {

    ExpressionNode* current = Factor();
    while(true) {
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == TIMES_TOKEN) {
            Match(tt);
            current = new TimesNode(current, Factor());
        }
        else if(tt == DIVIDE_TOKEN) {
            Match(tt);
            current = new DivideNode(current, Factor());
        }
        else {
            return current;
        }
    }
}

ExpressionNode* ParserClass::Factor() {
    ExpressionNode* en;
    while(true){
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == IDENTIFIER_TOKEN) {
            en = Identifier();
            return en;
        }
        else if(tt == INTEGER_TOKEN) {
            en = Integer();
            return en;
        }
        else if(tt == LEFT_PAREN_TOKEN) {
            Match(tt);
            en = Expression();
            Match(RIGHT_PAREN_TOKEN);
            return en;
        }
        else {
            std::cout << "Error: Expected IDENTIFIER_TOKEN, INTEGER_TOKEN, or LPAREN_TOKEN, but got " << tt << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

TokenClass ParserClass::Match(TokenType expectedType) {
    TokenClass tc = mScanner->GetNextToken();
    // MSG("Matched " << gTokenTypeNames[tc.GetTokenType()] << " with " << gTokenTypeNames[expectedType]);
    TokenType tt = tc.GetTokenType();
    if(tt != expectedType)
    {
        std::cout << "Error: Expected " << gTokenTypeNames[expectedType] << ", but got " << gTokenTypeNames[tt] <<  std::endl;
        exit(EXIT_FAILURE);
    }
    return tc;
}

IdentifierNode* ParserClass::Identifier() {
    // MSG("Creating IdentifierNode");
    TokenClass tc = Match(IDENTIFIER_TOKEN);
    IdentifierNode* in = new IdentifierNode(tc.GetLexeme(), mSymbolTable);
    return in;

}

IntegerNode* ParserClass::Integer() {
    // MSG("Creating IntegerNode");
    TokenClass tc = Match(INTEGER_TOKEN);
    IntegerNode* in = new IntegerNode(atoi(tc.GetLexeme().c_str()));
    return in;
}





