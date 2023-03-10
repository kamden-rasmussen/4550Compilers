#include "Node.h"
#include "Debug.h"

Node::~Node(){
}

StatementNode::StatementNode(){
    // MSG("Creating StatementNode");
}

StatementNode::~StatementNode(){
    // MSG("Destroying StatementNode");
}

StartNode::StartNode(ProgramNode *programNode){
    this->programNode = programNode;
    MSG("Creating StartNode");
}

StartNode::~StartNode(){
    delete this->programNode;
    MSG("Destroying StartNode");
}

ProgramNode::ProgramNode(BlockNode *blockNode){
    this->blockNode = blockNode;
    MSG("Creating ProgramNode");
}

ProgramNode::~ProgramNode(){
    delete this->blockNode;
    MSG("Destroying ProgramNode");
}

BlockNode::BlockNode(StatementGroupNode *statementGroupNode){
    this->statementGroupNode = statementGroupNode;
    MSG("Creating BlockNode");
}

BlockNode::~BlockNode(){
    delete this->statementGroupNode;
    MSG("Destroying BlockNode");
}

StatementGroupNode::StatementGroupNode(){
    MSG("Creating StatementGroupNode");
}

StatementGroupNode::~StatementGroupNode(){
    for(int i = 0; i < this->statementNodes.size(); i++){
        delete this->statementNodes[i];
    }
    MSG("Destroying StatementGroupNode");
}

void StatementGroupNode::AddStatement(StatementNode *statementNode){
    this->statementNodes.push_back(statementNode);
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode *identifierNode){
    this->identifierNode = identifierNode;
    MSG("Creating DeclarationStatementNode");
}

DeclarationStatementNode::~DeclarationStatementNode(){
    delete this->identifierNode;
    MSG("Destroying DeclarationStatementNode");
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode){
    this->identifierNode = identifierNode;
    this->expressionNode = expressionNode;
    MSG("Creating AssignmentStatementNode");
}

AssignmentStatementNode::~AssignmentStatementNode(){
    delete this->identifierNode;
    delete this->expressionNode;
    MSG("Destroying AssignmentStatementNode");
}

CoutStatementNode::CoutStatementNode(ExpressionNode *expressionNode){
    this->expressionNode = expressionNode;
    MSG("Creating CoutStatementNode");
}

CoutStatementNode::~CoutStatementNode(){
    delete this->expressionNode;
    MSG("Destroying CoutStatementNode");
}

ExpressionNode::ExpressionNode(){
    // MSG("Creating ExpressionNode");
}

ExpressionNode::~ExpressionNode(){
    // MSG("Destroying ExpressionNode");
}

int ExpressionNode::Evaluate(){
    return 0;
}

IdentifierNode::IdentifierNode(std::string name, SymbolTableClass *symbolTable){
    this->name = name;
    this->symbolTable = symbolTable;
}

void IdentifierNode::DeclareVariable(){
    this->symbolTable->AddEntry(this->name);
}
void IdentifierNode::SetValue(int value){
    this->symbolTable->SetValue(this->name, value);
}

int IdentifierNode::GetIndex(){
    return this->symbolTable->GetIndex(this->name);
}

IntegerNode::IntegerNode(int value){
    this->value = value;
    MSG("Creating IntegerNode");
}

IntegerNode::~IntegerNode(){
    MSG("Destroying IntegerNode");
}

int IntegerNode::Evaluate(){
    return this->value;
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right){
    this->left = left;
    this->right = right;
    // MSG("Creating BinaryOperatorNode");
}

BinaryOperatorNode::~BinaryOperatorNode(){
    delete left;
    delete right;
    // MSG("Destroying BinaryOperatorNode");
}

PlusNode::PlusNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    MSG("Creating PlusNode");
}

PlusNode::~PlusNode(){
    MSG("Destroying PlusNode");
}

int PlusNode::Evaluate(){
    return left->Evaluate() + right->Evaluate();
}

MinusNode::MinusNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    MSG("Creating MinusNode");
}

MinusNode::~MinusNode(){
    MSG("Destroying MinusNode");
}

int MinusNode::Evaluate(){
    return left->Evaluate() - right->Evaluate();
}

TimesNode::TimesNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    MSG("Creating TimesNode");
}

TimesNode::~TimesNode(){
    MSG("Destroying TimesNode");
}

int TimesNode::Evaluate(){
    return left->Evaluate() * right->Evaluate();
}

DivideNode::DivideNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    MSG("Creating DivideNode");
}

DivideNode::~DivideNode(){
    MSG("Destroying DivideNode");
}

int DivideNode::Evaluate(){
    return left->Evaluate() / right->Evaluate();
}

LessNode::LessNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    MSG("Creating LessNode");
}

LessNode::~LessNode(){
    MSG("Destroying LessNode");
}

int LessNode::Evaluate(){
    return left->Evaluate() < right->Evaluate() ? 1 : 0;
}

LessEqualNode::LessEqualNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    MSG("Creating LessEqualNode");
}

LessEqualNode::~LessEqualNode(){
    MSG("Destroying LessEqualNode");
}

int LessEqualNode::Evaluate(){
    return left->Evaluate() <= right->Evaluate() ? 1 : 0;
}

GreaterNode::GreaterNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    MSG("Creating GreaterNode");
}

GreaterNode::~GreaterNode(){
    MSG("Destroying GreaterNode");
}

int GreaterNode::Evaluate(){
    return left->Evaluate() > right->Evaluate() ? 1 : 0;
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    MSG("Creating GreaterEqualNode");
}

GreaterEqualNode::~GreaterEqualNode(){
    MSG("Destroying GreaterEqualNode");
}

int GreaterEqualNode::Evaluate(){
    return left->Evaluate() >= right->Evaluate() ? 1 : 0;
}

EqualNode::EqualNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    MSG("Creating EqualNode");
}

EqualNode::~EqualNode(){
    MSG("Destroying EqualNode");
}

int EqualNode::Evaluate(){
    return left->Evaluate() == right->Evaluate() ? 1 : 0;
}

NotEqualNode::NotEqualNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    MSG("Creating NotEqualNode");
}

NotEqualNode::~NotEqualNode(){
    MSG("Destroying NotEqualNode");
}

int NotEqualNode::Evaluate(){
    return left->Evaluate() != right->Evaluate() ? 1 : 0;
}
