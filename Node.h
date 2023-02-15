#pragma once
#include <vector>
#include <string>
#include "Symbol.h"

class Node;
class StatementNode;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;
class ExpressionNode;
class IdentifierNode;
class IntegerNode;
class BinaryOperatorNode;
class PlusNode;

// Abstract base classes
class Node{
    public:
        virtual ~Node();
};

class StatementNode : public Node{
    public:
        StatementNode();
        ~StatementNode();
};

//Classes
class StartNode : public Node{
    public:
        StartNode(ProgramNode *programNode);
        ~StartNode();
    private:
        ProgramNode *programNode;
};

class ProgramNode : public Node{
    public:
        ProgramNode(BlockNode *blockNode);
        ~ProgramNode();
    private:
        BlockNode *blockNode;
};

class BlockNode : public Node{
    public:
        BlockNode(StatementGroupNode *statementGroupNode);
        ~BlockNode();
    private:
        StatementGroupNode *statementGroupNode;
};

class StatementGroupNode : public Node{
    public:
        StatementGroupNode();
        ~StatementGroupNode();
        void AddStatement(StatementNode *statementNode);
    private:
        std::vector<StatementNode *> statementNodes;
};

class DeclarationStatementNode : public StatementNode{
    public:
        DeclarationStatementNode(IdentifierNode *identifierNode);
        ~DeclarationStatementNode();
    private:
        IdentifierNode *identifierNode;
};

class AssignmentStatementNode : public StatementNode{
    public:
        AssignmentStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
        ~AssignmentStatementNode();
    private:
        IdentifierNode *identifierNode;
        ExpressionNode *expressionNode;
};

class CoutStatementNode : public StatementNode{
    public:
        CoutStatementNode(ExpressionNode *expressionNode);
        ~CoutStatementNode();
    private:
        ExpressionNode *expressionNode;
};

class ExpressionNode{
    public:
        ExpressionNode();
        virtual ~ExpressionNode();
        virtual int Evaluate();
};

class IntegerNode : public ExpressionNode{
    public:
        IntegerNode(int value);
        ~IntegerNode();
        int Evaluate();
    private:
        int value;
};

class IdentifierNode : public ExpressionNode{
    public:
        IdentifierNode(std::string label, SymbolTableClass *symbolTable); 
        void DeclareVariable();
        void SetValue(int value);
        int GetIndex();
    private:
        SymbolTableClass *symbolTable;
        std::string name;
};

class BinaryOperatorNode : public ExpressionNode{
    public:
        BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right);
        ~BinaryOperatorNode();
    protected:
        ExpressionNode *left;
        ExpressionNode *right;
};

class PlusNode : public BinaryOperatorNode{
    public:
        PlusNode(ExpressionNode *left, ExpressionNode *right);
        ~PlusNode();
        int Evaluate();
};
