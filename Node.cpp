#include "Node.h"
#include "Debug.h"
#include <cmath>

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
    // MSG("Creating StartNode");
}

StartNode::~StartNode(){
    delete this->programNode;
    // MSG("Destroying StartNode");
}

void StartNode::Interpret(){
    // MSG("Interpreting StartNode")
    this->programNode->Interpret();
}

void StartNode::Code(InstructionsClass &machineCode){
	this->programNode->Code(machineCode);
}

ProgramNode::ProgramNode(BlockNode *blockNode){
    this->blockNode = blockNode;
    // MSG("Creating ProgramNode");
}

ProgramNode::~ProgramNode(){
    delete this->blockNode;
    // MSG("Destroying ProgramNode");
}

void ProgramNode::Interpret(){
    // MSG("Interpreting ProgramNode")
    this->blockNode->Interpret();
}

void ProgramNode::Code(InstructionsClass &machineCode){
    this->blockNode->Code(machineCode);
}

BlockNode::BlockNode(StatementGroupNode *statementGroupNode){
    this->statementGroupNode = statementGroupNode;
    // MSG("Creating BlockNode");
}

BlockNode::~BlockNode(){
    delete this->statementGroupNode;
    // MSG("Destroying BlockNode");
}

void BlockNode::Interpret(){
    // MSG("Interpreting BlockNode")
    this->statementGroupNode->Interpret();
}

void BlockNode::Code(InstructionsClass &machineCode){
    this->statementGroupNode->Code(machineCode);
}

StatementGroupNode::StatementGroupNode(){
    // MSG("Creating StatementGroupNode");
}

StatementGroupNode::~StatementGroupNode(){
    for(int i = 0; i < this->statementNodes.size(); i++){
        delete this->statementNodes[i];
    }
    // MSG("Destroying StatementGroupNode");
}

void StatementGroupNode::AddStatement(StatementNode *statementNode){
    this->statementNodes.push_back(statementNode);
}

void StatementGroupNode::Interpret(){
    // MSG("Interpreting StatementGroupNode")
    for(int i = 0; i < this->statementNodes.size(); i++){
        this->statementNodes[i]->Interpret();
    }
}

void StatementGroupNode::Code(InstructionsClass &machineCode){
    for(int i = 0; i < this->statementNodes.size(); i++){
        this->statementNodes[i]->Code(machineCode);
    }
}

DeclarationStatementNode::DeclarationStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode){
    this->identifierNode = identifierNode;
    this->expressionNode = expressionNode;
    // MSG("Creating DeclarationStatementNode");
}

DeclarationStatementNode::~DeclarationStatementNode(){
    delete this->identifierNode;
    delete this->expressionNode;
    // MSG("Destroying DeclarationStatementNode");
}

void DeclarationStatementNode::Interpret(){
    if (this->expressionNode != NULL){
        this->identifierNode->DeclareVariable();
        this->identifierNode->SetValue(this->expressionNode->Evaluate());
    } else{
        this->identifierNode->DeclareVariable();
    }
}

void DeclarationStatementNode::Code(InstructionsClass &machineCode){
    this->identifierNode->DeclareVariable();
    if (this->expressionNode != NULL){
        this->expressionNode->CodeEvaluate(machineCode);
        machineCode.PopAndStore(this->identifierNode->GetIndex());
    }
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode){
    this->identifierNode = identifierNode;
    this->expressionNode = expressionNode;
    // MSG("Creating AssignmentStatementNode");
}

AssignmentStatementNode::~AssignmentStatementNode(){
    delete this->identifierNode;
    delete this->expressionNode;
    // MSG("Destroying AssignmentStatementNode");
}

void AssignmentStatementNode::Interpret(){
    this->identifierNode->SetValue(this->expressionNode->Evaluate());
}

void AssignmentStatementNode::Code(InstructionsClass &machineCode){
    this->expressionNode->CodeEvaluate(machineCode);
    machineCode.PopAndStore(this->identifierNode->GetIndex());

}

CoutStatementNode::CoutStatementNode(ExpressionNode *expressionNode){
    this->expressionNode = expressionNode;
    // MSG("Creating CoutStatementNode");
}

CoutStatementNode::~CoutStatementNode(){
    delete this->expressionNode;
    // MSG("Destroying CoutStatementNode");
}

void CoutStatementNode::Interpret(){
    std::cout << this->expressionNode->Evaluate() << std::endl;
}

void CoutStatementNode::Code(InstructionsClass &machineCode){
    this->expressionNode->CodeEvaluate(machineCode);
    machineCode.PopAndWrite();
}

PrintStatementNode::PrintStatementNode(ExpressionNode *expressionNode){
    this->expressionNode = expressionNode;
    // MSG("Creating PrintStatementNode");
}

PrintStatementNode::~PrintStatementNode(){
    delete this->expressionNode;
    // MSG("Destroying PrintStatementNode");
}

void PrintStatementNode::Interpret(){
    std::cout << this->expressionNode->Evaluate() << std::endl;
}

void PrintStatementNode::Code(InstructionsClass &machineCode){
    this->expressionNode->CodeEvaluate(machineCode);
    machineCode.PopAndWrite();
}

IfStatementNode::IfStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode1, StatementNode *statementNode2){
    this->expressionNode = expressionNode;
    this->statementNode1 = statementNode1;
    this->statementNode2 = statementNode2;
    // MSG("Creating IfStatementNode");
}

IfStatementNode::~IfStatementNode(){
    delete this->expressionNode;
    delete this->statementNode1;
    delete this->statementNode2;
    // MSG("Destroying IfStatementNode");
}

void IfStatementNode::Interpret(){
    // MSG("Interpreting IfStatementNode")
    if(this->expressionNode->Evaluate() != 0){
        // MSG("Interpreting IfStatementNode (true)")
        this->statementNode1->Interpret();
    } else {
        if (this->statementNode2 != NULL) {
            // MSG("Interpreting IfStatementNode (false)")
            this->statementNode2->Interpret();
        }
    }
}

void IfStatementNode::Code(InstructionsClass &machineCode){
    if (this->statementNode2 == NULL){
        this->expressionNode->CodeEvaluate(machineCode);
        unsigned char * InsertAddress = machineCode.SkipIfZeroStack();
        unsigned char * address1 = machineCode.GetAddress();
        this->statementNode1->Code(machineCode);
        unsigned char * address2 = machineCode.GetAddress();
        machineCode.SetOffset(InsertAddress, (int)(address2 - address1));
    } else {
        this->expressionNode->CodeEvaluate(machineCode);
        unsigned char * InsertAddress = machineCode.SkipIfZeroStack();
        unsigned char * address1 = machineCode.GetAddress();
        this->statementNode1->Code(machineCode);
        unsigned char * InsertAddress2 = machineCode.Jump();
        unsigned char * address2 = machineCode.GetAddress();
        //jump over satement 2
        this->statementNode2->Code(machineCode);
        unsigned char * address3 = machineCode.GetAddress();
        machineCode.SetOffset(InsertAddress, (int)(address2 - address1));
        machineCode.SetOffset(InsertAddress2, (int)(address3 - address2));
    }
}

WhileStatementNode::WhileStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode){
    this->expressionNode = expressionNode;
    this->statementNode = statementNode;
    // MSG("Creating WhileStatementNode");
}

WhileStatementNode::~WhileStatementNode(){
    delete this->expressionNode;
    delete this->statementNode;
    // MSG("Destroying WhileStatementNode");
}

void WhileStatementNode::Interpret(){
    while(this->expressionNode->Evaluate() != 0){
        this->statementNode->Interpret();
    }
}

void WhileStatementNode::Code(InstructionsClass &machineCode){
  unsigned char *address1 = machineCode.GetAddress();
  this->expressionNode->CodeEvaluate(machineCode);
  unsigned char *insertAddressSkip = machineCode.SkipIfZeroStack();
  unsigned char *address2 = machineCode.GetAddress();
  this->statementNode->Code(machineCode);
  unsigned char *insertAddressJump = machineCode.Jump();
  unsigned char *address3 = machineCode.GetAddress();
  machineCode.SetOffset(insertAddressSkip, (int)(address3 - address2));
  machineCode.SetOffset(insertAddressJump, (int)(address1 - address3));
}

ExpressionNode::ExpressionNode(){
    // MSG("Creating ExpressionNode");
}

ExpressionNode::~ExpressionNode(){
    // MSG("Destroying ExpressionNode");
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

int IdentifierNode::Evaluate(){
    // MSG("Evaluating IdentifierNode")
    // MSG("Getting value of " << this->name)
    return this->symbolTable->GetValue(this->name);
}

void IdentifierNode::CodeEvaluate(InstructionsClass &machineCode){
    machineCode.PushVariable(this->GetIndex());
}

IntegerNode::IntegerNode(int value){
    this->value = value;
    // MSG("Creating IntegerNode");
}

IntegerNode::~IntegerNode(){
    // MSG("Destroying IntegerNode");
}

int IntegerNode::Evaluate(){
    // MSG("Evaluating IntegerNode")
    return this->value;
}

void IntegerNode::CodeEvaluate(InstructionsClass &machineCode){
    machineCode.PushValue(this->value);
}

BinaryOperatorNode::BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right){
    this->left = left;
    this->right = right;
    // MSG("Creating BinaryOperatorNode");
}

BinaryOperatorNode::~BinaryOperatorNode(){
    delete this->left;
    delete this->right;
    // MSG("Destroying BinaryOperatorNode");
}

PlusNode::PlusNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    // MSG("Creating PlusNode");
}

PlusNode::~PlusNode(){
    // MSG("Destroying PlusNode");
}

int PlusNode::Evaluate(){
    // MSG("Evaluating PlusNode")
    return this->left->Evaluate() + this->right->Evaluate();
}

void PlusNode::CodeEvaluate(InstructionsClass &machineCode){
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopAddPush();
}

MinusNode::MinusNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    // MSG("Creating MinusNode");
}

MinusNode::~MinusNode(){
    // MSG("Destroying MinusNode");
}

int MinusNode::Evaluate(){
    return this->left->Evaluate() - this->right->Evaluate();
}

void MinusNode::CodeEvaluate(InstructionsClass &machineCode){
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopSubPush();
}

TimesNode::TimesNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    // MSG("Creating TimesNode");
}

TimesNode::~TimesNode(){
    // MSG("Destroying TimesNode");
}

int TimesNode::Evaluate(){
    return this->left->Evaluate() * this->right->Evaluate();
}

void TimesNode::CodeEvaluate(InstructionsClass &machineCode){
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopMulPush();
}

ExponentNode::ExponentNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    // MSG("Creating ExponentNode");
}

ExponentNode::~ExponentNode(){
    // MSG("Destroying ExponentNode");
}

int ExponentNode::Evaluate(){
    return (int)pow(this->left->Evaluate(), this->right->Evaluate());
}

void ExponentNode::CodeEvaluate(InstructionsClass &machineCode){
    // this->left->CodeEvaluate(machineCode);
    // this->right->CodeEvaluate(machineCode);
    // machineCode.PopPopExpPush();
}

DivideNode::DivideNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    // MSG("Creating DivideNode");
}

DivideNode::~DivideNode(){
    // MSG("Destroying DivideNode");
}

int DivideNode::Evaluate(){
    return this->left->Evaluate() / this->right->Evaluate();
}

void DivideNode::CodeEvaluate(InstructionsClass &machineCode){
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopDivPush();
}

LessNode::LessNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    // MSG("Creating LessNode");
}

LessNode::~LessNode(){
    // MSG("Destroying LessNode");
}

int LessNode::Evaluate(){
    return left->Evaluate() < right->Evaluate() ? 1 : 0;
}

void LessNode::CodeEvaluate(InstructionsClass &machineCode){
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopLessPush();
}

LessEqualNode::LessEqualNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    // MSG("Creating LessEqualNode");
}

LessEqualNode::~LessEqualNode(){
    // MSG("Destroying LessEqualNode");
}

int LessEqualNode::Evaluate(){
    return left->Evaluate() <= right->Evaluate() ? 1 : 0;
}

void LessEqualNode::CodeEvaluate(InstructionsClass &machineCode){
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopLessEqualPush();
}

GreaterNode::GreaterNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    // MSG("Creating GreaterNode");
}

GreaterNode::~GreaterNode(){
    // MSG("Destroying GreaterNode");
}

int GreaterNode::Evaluate(){
    return left->Evaluate() > right->Evaluate() ? 1 : 0;
}

void GreaterNode::CodeEvaluate(InstructionsClass &machineCode){
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopGreaterPush();
}

GreaterEqualNode::GreaterEqualNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    // MSG("Creating GreaterEqualNode");
}

GreaterEqualNode::~GreaterEqualNode(){
    // MSG("Destroying GreaterEqualNode");
}

int GreaterEqualNode::Evaluate(){
    return left->Evaluate() >= right->Evaluate() ? 1 : 0;
}

void GreaterEqualNode::CodeEvaluate(InstructionsClass &machineCode){
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopGreaterEqualPush();
}

EqualNode::EqualNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    // MSG("Creating EqualNode");
}

EqualNode::~EqualNode(){
    // MSG("Destroying EqualNode");
}

int EqualNode::Evaluate(){
    return left->Evaluate() == right->Evaluate() ? 1 : 0;
}

void EqualNode::CodeEvaluate(InstructionsClass &machineCode){
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopEqualPush();
}

NotEqualNode::NotEqualNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    // MSG("Creating NotEqualNode");
}

NotEqualNode::~NotEqualNode(){
    // MSG("Destroying NotEqualNode");
}

int NotEqualNode::Evaluate(){
    return left->Evaluate() != right->Evaluate() ? 1 : 0;
}

void NotEqualNode::CodeEvaluate(InstructionsClass &machineCode){
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopNotEqualPush();
}

AndNode::AndNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    // MSG("Creating AndNode");
}

AndNode::~AndNode(){
    // MSG("Destroying AndNode");
}

int AndNode::Evaluate(){
    return left->Evaluate() && right->Evaluate();
}

void AndNode::CodeEvaluate(InstructionsClass &machineCode){
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopAndPush();
}

OrNode::OrNode(ExpressionNode *left, ExpressionNode *right) : BinaryOperatorNode(left, right){
    // MSG("Creating OrNode");
}

OrNode::~OrNode(){
    // MSG("Destroying OrNode");
}

int OrNode::Evaluate(){
    return left->Evaluate() || right->Evaluate();
}

void OrNode::CodeEvaluate(InstructionsClass &machineCode){
    this->left->CodeEvaluate(machineCode);
    this->right->CodeEvaluate(machineCode);
    machineCode.PopPopOrPush();
}
