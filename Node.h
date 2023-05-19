#pragma once
#include <vector>
#include <string>
#include "Symbol.h"
#include "Instructions.h"

class Node;
class StatementNode;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class PlusEqualsStatementNode;
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
        virtual void Code(InstructionsClass &machineCode) = 0;
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
        virtual void Code(InstructionsClass &machineCode);
    private:
        ProgramNode *programNode;
};

class ProgramNode : public Node{
    public:
        ProgramNode(BlockNode *blockNode);
        ~ProgramNode();
        virtual void Interpret();
        virtual void Code(InstructionsClass &machineCode);
    private:
        BlockNode *blockNode;
};

class BlockNode : public StatementNode{
    public:
        BlockNode(StatementGroupNode *statementGroupNode);
        ~BlockNode();
        virtual void Interpret();
        virtual void Code(InstructionsClass &machineCode);
    private:
        StatementGroupNode *statementGroupNode;
};

class StatementGroupNode : public Node{
    public:
        StatementGroupNode();
        ~StatementGroupNode();
        void AddStatement(StatementNode *statementNode);
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        std::vector<StatementNode *> statementNodes;
};

class DeclarationStatementNode : public StatementNode{
    public:
        DeclarationStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
        ~DeclarationStatementNode();
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        IdentifierNode *identifierNode;
        ExpressionNode *expressionNode;
};

class AssignmentStatementNode : public StatementNode{
    public:
        AssignmentStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
        ~AssignmentStatementNode();
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        IdentifierNode *identifierNode;
        ExpressionNode *expressionNode;
};

class CoutStatementNode : public StatementNode{
    public:
        CoutStatementNode(std::vector<ExpressionNode *> expressionNodes);
        ~CoutStatementNode();
        void AddExpression(ExpressionNode *expressionNode);
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        std::vector<ExpressionNode *> expressionNodes;
};

class PrintStatementNode : public StatementNode{
    public:
        PrintStatementNode(ExpressionNode *expressionNode);
        ~PrintStatementNode();
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        ExpressionNode *expressionNode;
};

class IfStatementNode : public StatementNode{
    public:
        IfStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode1, StatementNode *statementNode2);
        ~IfStatementNode();
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        ExpressionNode *expressionNode;
        StatementNode *statementNode1;
        StatementNode *statementNode2;

};

class WhileStatementNode : public StatementNode{
    public:
        WhileStatementNode(ExpressionNode *expressionNode, StatementNode *statementNode);
        ~WhileStatementNode();
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        ExpressionNode *expressionNode;
        StatementNode *statementNode;
};
class ExpressionNode{
    public:
        ExpressionNode();
        virtual ~ExpressionNode();
        virtual int Evaluate() = 0;
        virtual void CodeEvaluate(InstructionsClass &machineCode) = 0;
};

class IntegerNode : public ExpressionNode{
    public:
        IntegerNode(int value);
        ~IntegerNode();
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
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
        void CodeEvaluate(InstructionsClass &machineCode);
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
        void CodeEvaluate(InstructionsClass &machineCode);
};

class PlusEqualStatementNode : public AssignmentStatementNode{
    public:
        PlusEqualStatementNode(IdentifierNode *identifierNode, ExpressionNode *expressionNode);
        ~PlusEqualStatementNode();
        void Interpret();
        void Code(InstructionsClass &machineCode);
    private:
        IdentifierNode *identifierNode;
        ExpressionNode *expressionNode;
};

class MinusNode : public BinaryOperatorNode{
    public:
        MinusNode(ExpressionNode *left, ExpressionNode *right);
        ~MinusNode();
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class TimesNode : public BinaryOperatorNode{
    public:
        TimesNode(ExpressionNode *left, ExpressionNode *right);
        ~TimesNode();
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class ExponentNode : public BinaryOperatorNode{
    public:
        ExponentNode(ExpressionNode *left, ExpressionNode *right);
        ~ExponentNode();
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class DivideNode : public BinaryOperatorNode{
    public:
        DivideNode(ExpressionNode *left, ExpressionNode *right);
        ~DivideNode();
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class LessNode : public BinaryOperatorNode{
    public:
        LessNode(ExpressionNode *left, ExpressionNode *right);
        ~LessNode();
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class LessEqualNode : public BinaryOperatorNode{
    public:
        LessEqualNode(ExpressionNode *left, ExpressionNode *right);
        ~LessEqualNode();
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class GreaterNode : public BinaryOperatorNode{
    public:
        GreaterNode(ExpressionNode *left, ExpressionNode *right);
        ~GreaterNode();
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class GreaterEqualNode : public BinaryOperatorNode{
    public:
        GreaterEqualNode(ExpressionNode *left, ExpressionNode *right);
        ~GreaterEqualNode();
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class EqualNode : public BinaryOperatorNode{
    public:
        EqualNode(ExpressionNode *left, ExpressionNode *right);
        ~EqualNode();
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class NotEqualNode : public BinaryOperatorNode{
    public:
        NotEqualNode(ExpressionNode *left, ExpressionNode *right);
        ~NotEqualNode();
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class AndNode : public BinaryOperatorNode{
    public:
        AndNode(ExpressionNode *left, ExpressionNode *right);
        ~AndNode();
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

class OrNode : public BinaryOperatorNode{
    public:
        OrNode(ExpressionNode *left, ExpressionNode *right);
        ~OrNode();
        int Evaluate();
        void CodeEvaluate(InstructionsClass &machineCode);
};

