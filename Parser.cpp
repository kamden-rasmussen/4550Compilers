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
    // MSG("START");
    ProgramNode* pn = Program();
    StartNode* sn = new StartNode(pn); // order seems backwards
    Match(ENDFILE_TOKEN);
    // MSG("END");
    return sn;
}

ProgramNode* ParserClass::Program() {
    // MSG("Program Starting NOW");
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LEFT_PAREN_TOKEN);
    Match(RIGHT_PAREN_TOKEN);
    BlockNode* bn = Block();
    ProgramNode* pn = new ProgramNode(bn);
    // MSG("Program Closing")
    return pn;
}

BlockNode* ParserClass::Block() {
    // MSG("Block Starting");
    Match(LEFT_CURLY_TOKEN);
    StatementGroupNode* sgn = StatementGroup();
    Match(RIGHT_CURLY_TOKEN);
    BlockNode* bn = new BlockNode(sgn);
    // MSG("Block Closing")
    return bn;
}

StatementGroupNode* ParserClass::StatementGroup() {
    // MSG("StatementGroup Starting");
    StatementGroupNode* sgn = new StatementGroupNode();
    while(true) {
        StatementNode* sn = Statement();
        if(sn != NULL) {
            sgn->AddStatement(sn);
        }
        else {
            break;
        }
    }
    return sgn;
}

StatementNode* ParserClass::Statement() {
    // MSG("Statement Starting")
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == INT_TOKEN) {
        // MSG("Statement is DeclarationStatement")
        DeclarationStatementNode* dsn = DeclarationStatement();
        return dsn;
    }
    else if(tt == IDENTIFIER_TOKEN) {
        // MSG("Statement is AssignmentStatement")
        AssignmentStatementNode* asn = AssignmentStatement();
        return asn;
    }
    else if(tt == COUT_TOKEN) {
        // MSG("Statement is CoutStatement")
        CoutStatementNode* csn = CoutStatement();
        return csn;
    }
    else if (tt == PRINT_TOKEN) {
        // MSG("Statement is PrintStatement")
        PrintStatementNode* psn = PrintStatement();
        return psn;
    }
    else if(tt == LEFT_CURLY_TOKEN) {
        // MSG("Statement is Block")
        BlockNode* bn = Block();
        return bn;
    }
    else if (tt == IF_TOKEN) {
        // MSG("Statement is IfStatement")
        IfStatementNode* isn = IfStatement();
        return isn;
    }
    else if (tt == WHILE_TOKEN) {
        // MSG("Statement is WhileStatement")
        WhileStatementNode* isn = WhileStatement();
        return isn;
    }
    else {
        // MSG("Statement is NULL")
        return NULL;
    }
}

DeclarationStatementNode* ParserClass::DeclarationStatement() {
    // MSG("DeclarationStatement Starting")
    Match(INT_TOKEN);
    IdentifierNode* in = Identifier();
    Match(SEMICOLON_TOKEN);
    // MSG("DeclarationStatement Ending")
    DeclarationStatementNode* dsn = new DeclarationStatementNode(in);
    return dsn;
}

AssignmentStatementNode* ParserClass::AssignmentStatement() {
    // MSG("AssignmentStatement Starting")
    IdentifierNode* in = Identifier();
    Match(ASSIGNMENT_TOKEN);
    ExpressionNode* en = Expression();
    Match(SEMICOLON_TOKEN);
    // MSG("AssignmentStatement Ending")
    AssignmentStatementNode* asn = new AssignmentStatementNode(in, en);
    return asn;
}

CoutStatementNode* ParserClass::CoutStatement() {
    // MSG("Starting CoutStatement")
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);
    ExpressionNode* en = Expression();
    Match(SEMICOLON_TOKEN);
    // MSG("Ending CoutStatement")
    CoutStatementNode* csn = new CoutStatementNode(en);
    return csn;
}

PrintStatementNode* ParserClass::PrintStatement() {
    // MSG("Starting PrintStatement")
    Match(PRINT_TOKEN);
    Match(LEFT_PAREN_TOKEN);
    ExpressionNode* en = Expression();
    Match(RIGHT_PAREN_TOKEN);
    Match(SEMICOLON_TOKEN);
    // MSG("Ending PrintStatement")
    PrintStatementNode* psn = new PrintStatementNode(en);
    return psn;
}

IfStatementNode* ParserClass::IfStatement() {
    // MSG("Starting IfStatement")
    Match(IF_TOKEN);
    Match(LEFT_PAREN_TOKEN);
    ExpressionNode* en = Expression();
    Match(RIGHT_PAREN_TOKEN);
    BlockNode* bn = Block();
    // peek next token to see if it is an else statement

    if(mScanner->PeekNextToken().GetTokenType() == ELSE_TOKEN) {

        Match(ELSE_TOKEN);
        BlockNode* bn2 = Block();
        IfStatementNode* isn = new IfStatementNode(en, bn, bn2);
        return isn;
    } 
    IfStatementNode* isn = new IfStatementNode(en, bn, NULL);
    return isn;
}

WhileStatementNode* ParserClass::WhileStatement() {
    // MSG("Starting WhileStatement")
    Match(WHILE_TOKEN);
    Match(LEFT_PAREN_TOKEN);
    ExpressionNode* en = Expression();
    Match(RIGHT_PAREN_TOKEN);
    BlockNode* bn = Block();
    // MSG("Ending WhileStatement")
    WhileStatementNode* wsn = new WhileStatementNode(en, bn);
    return wsn;
}

ExpressionNode* ParserClass::Expression() {
    // MSG("Starting Expression")
    ExpressionNode* en = Or();
    // MSG("Ending Expression")
    return en;
}

ExpressionNode* ParserClass::Or() {
    // MSG("Starting Or")
    ExpressionNode* current = And();
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == OR_TOKEN) {
        Match(tt);
        current = new OrNode(current, And());
    }
    // MSG("Ending Or")
    return current;
}

ExpressionNode* ParserClass::And() {
    // MSG("Starting And")
    ExpressionNode* current = Relational();
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if (tt == AND_TOKEN) {
        Match(tt);
        current = new AndNode(current, Relational());
    }
    // MSG("Ending And")
    return current;
}

ExpressionNode* ParserClass::Relational() {
    // MSG("Starting Relational")

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
    // MSG("Ending Relational")
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

