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
        virtual void Interpret() = 0;
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
        virtual void Interpret();
    private:
        ProgramNode *programNode;
};

class ProgramNode : public Node{
    public:
        ProgramNode(BlockNode *blockNode);
        ~ProgramNode();
        virtual void Interpret();
    private:
        BlockNode *blockNode;
};

class BlockNode : public StatementNode{
    public:
        BlockNode(StatementGroupNode *statementGroupNode);
        ~BlockNode();
        virtual void Interpret();
    private:
        StatementGroupNode *statementGroupNode;
};

class StatementGroupNode : public Node{
    public:
        StatementGroupNode();
        ~StatementGroupNode();
        void AddStatement(StatementNode *statementNode);
        void Interpret();
    private:
        std::vector<StatementNode *> statementNodes;
};

class DeclarationStatementNode : public StatementNode{
    public:
        DeclarationStatementNode(IdentifierNode *identifierNode);
        ~DeclarationStatementNode();
        void Interpret();
    private:
        IdentifierNode *identifierNode;
};

class AssignmentStatementNode : public StatementNode{
    public:
        AssignmentStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
        ~AssignmentStatementNode();
        void Interpret();
    private:
        IdentifierNode *identifierNode;
        ExpressionNode *expressionNode;
};

class CoutStatementNode : public StatementNode{
    public:
        CoutStatementNode(ExpressionNode *expressionNode);
        ~CoutStatementNode();
        void Interpret();
    private:
        ExpressionNode *expressionNode;
};

class IfStatementNode : public StatementNode{
    public:
        IfStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode);
        ~IfStatementNode();
        void Interpret();
    private:
        ExpressionNode *expressionNode;
        StatementNode *statementNode;
};

class WhileStatementNode : public StatementNode{
    public:
        WhileStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode);
        ~WhileStatementNode();
        void Interpret();
    private:
        ExpressionNode *expressionNode;
        StatementNode *statementNode;
};
class ExpressionNode{
    public:
        ExpressionNode();
        virtual ~ExpressionNode();
        virtual int Evaluate() = 0;
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
        int Evaluate();
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

class MinusNode : public BinaryOperatorNode{
    public:
        MinusNode(ExpressionNode *left, ExpressionNode *right);
        ~MinusNode();
        int Evaluate();
};

class TimesNode : public BinaryOperatorNode{
    public:
        TimesNode(ExpressionNode *left, ExpressionNode *right);
        ~TimesNode();
        int Evaluate();
};

class DivideNode : public BinaryOperatorNode{
    public:
        DivideNode(ExpressionNode *left, ExpressionNode *right);
        ~DivideNode();
        int Evaluate();
};

class LessNode : public BinaryOperatorNode{
    public:
        LessNode(ExpressionNode *left, ExpressionNode *right);
        ~LessNode();
        int Evaluate();
};

class LessEqualNode : public BinaryOperatorNode{
    public:
        LessEqualNode(ExpressionNode *left, ExpressionNode *right);
        ~LessEqualNode();
        int Evaluate();
};

class GreaterNode : public BinaryOperatorNode{
    public:
        GreaterNode(ExpressionNode *left, ExpressionNode *right);
        ~GreaterNode();
        int Evaluate();
};

class GreaterEqualNode : public BinaryOperatorNode{
    public:
        GreaterEqualNode(ExpressionNode *left, ExpressionNode *right);
        ~GreaterEqualNode();
        int Evaluate();
};

class EqualNode : public BinaryOperatorNode{
    public:
        EqualNode(ExpressionNode *left, ExpressionNode *right);
        ~EqualNode();
        int Evaluate();
};

class NotEqualNode : public BinaryOperatorNode{
    public:
        NotEqualNode(ExpressionNode *left, ExpressionNode *right);
        ~NotEqualNode();
        int Evaluate();
};

class AndNode : public BinaryOperatorNode{
    public:
        AndNode(ExpressionNode *left, ExpressionNode *right);
        ~AndNode();
        int Evaluate();
};

class OrNode : public BinaryOperatorNode{
    public:
        OrNode(ExpressionNode *left, ExpressionNode *right);
        ~OrNode();
        int Evaluate();
};

