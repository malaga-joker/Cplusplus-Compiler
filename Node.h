class Node;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class AssignmentStatementNode;
class CoutStatementNode;
class IfStatementNode;
class WhileStatementNode;
class PlusNode;
class MinusNode;
class MutiNode;
class DeviNode;
class ModNode;
class ExpressionNode;
class IntegerNode;
class IdentifierNode;
class EndlNode;
class BinaryOperatorNode;
class PlusAssignNode;
class MinusAssignNode;
class LessNode;
class LessEqulNode;
class GreaterNode;
class GreaterEqulNode;
class EqulNode;
class NotEqulNode;
class AndNode;
class OrNode;

#include<iostream>
#include<vector>
#include"VariableList.h"

using namespace std;

class Node{
	public:
		virtual void Interpret()=0;
		virtual ~Node(){}
};

class StartNode : public Node {
	public:
		StartNode(StatementGroupNode *sg);
		virtual ~StartNode();
		void Interpret();
		StatementGroupNode* getSgN() {return mSgNode;}
	private:
		StatementGroupNode* mSgNode;
};

class StatementGroupNode : public Node {
	public:
		StatementGroupNode(){}
		virtual ~StatementGroupNode();
		void AddStatement(StatementNode *sn);
		void Interpret();
		vector<StatementNode*> getSGVector() {return mStatementNodes;}
	private:
		vector<StatementNode*> mStatementNodes;
}; 

class StatementNode : public Node {
	public:
		virtual void Interpret()=0;
		virtual ~StatementNode(){}
};

class CoutStatementNode : public StatementNode {
	public:
		CoutStatementNode(){}
		virtual ~CoutStatementNode();
		void addExpression(ExpressionNode *en);
		void Interpret();
		vector<ExpressionNode*> getCVector() {return mExpressionNodes;}
	private:
		vector<ExpressionNode*> mExpressionNodes;
};

class DeclarationStatementNode : public StatementNode{
    public:
		DeclarationStatementNode(IdentifierNode* );
		virtual ~DeclarationStatementNode();
		void    Interpret(){}
    private:
		IdentifierNode*   mIndentiferNode;
};

class AssignmentStatementNode : public StatementNode{
    public:
		AssignmentStatementNode(){}
		AssignmentStatementNode(IdentifierNode*,ExpressionNode*);
		virtual ~AssignmentStatementNode();
		void    Interpret();
    private:
		IdentifierNode* in;
		ExpressionNode* en;
};

class PlusAssignNode : public AssignmentStatementNode {
	public:
		PlusAssignNode(IdentifierNode*, ExpressionNode*);
		void Interpret();
	private:
		IdentifierNode* in;
		ExpressionNode* en;
};

class MinusAssignNode : public AssignmentStatementNode {
	public:
		MinusAssignNode(IdentifierNode*, ExpressionNode*);
		void Interpret();
	private:
		IdentifierNode* in;
		ExpressionNode* en;
};

class MutiAssignNode : public AssignmentStatementNode {
	 public:
		MutiAssignNode(IdentifierNode*, ExpressionNode*);
		void Interpret();
	private:
		IdentifierNode* in;
		ExpressionNode* en;
};

class IfStatementNode : public StatementNode{
    public:
		IfStatementNode(ExpressionNode* ,StatementNode* );
		virtual ~IfStatementNode();
		void    Interpret();
    private:
		ExpressionNode* en;
		StatementNode*  sn;
};

class WhileStatementNode : public StatementNode{
    public:
		WhileStatementNode(ExpressionNode* ,StatementNode* );
		virtual ~WhileStatementNode();
		void    Interpret();
    private:
		ExpressionNode* en;
		StatementNode*  sn;
};

class ExpressionNode {
	public:
		virtual int Evaluate()=0;
		virtual ~ExpressionNode(){}
};

class BinaryOperatorNode : public ExpressionNode {
	public:
		BinaryOperatorNode(ExpressionNode *left, ExpressionNode *right);
		virtual int Evaluate()=0;
		virtual ~BinaryOperatorNode();
	protected:
		ExpressionNode *left;
		ExpressionNode *right;
};

class PlusNode : public BinaryOperatorNode {
	public:
		PlusNode(ExpressionNode *l, ExpressionNode *r);
		int Evaluate();
};

class MinusNode : public BinaryOperatorNode {
	public:
		MinusNode(ExpressionNode *l, ExpressionNode *r);
		virtual int Evaluate();
};

class MutiNode : public BinaryOperatorNode {
	public:
		MutiNode(ExpressionNode *l, ExpressionNode *r);
		virtual int Evaluate();
};

class DiviNode : public BinaryOperatorNode {
	public:
		DiviNode(ExpressionNode *l, ExpressionNode *r);
		virtual int Evaluate();
};

class ModNode : public BinaryOperatorNode {
	public:
		ModNode(ExpressionNode *l, ExpressionNode *r);
		virtual int Evaluate();
};

class LessNode : public BinaryOperatorNode {
	public:
		LessNode(ExpressionNode *l, ExpressionNode *r);
		virtual int Evaluate();
}; 

class LessEqulNode : public BinaryOperatorNode {
	public:
		LessEqulNode(ExpressionNode *l, ExpressionNode *r);
		virtual int Evaluate();
}; 

class GreaterNode : public BinaryOperatorNode {
	public:
		GreaterNode(ExpressionNode *l, ExpressionNode *r);
		virtual int Evaluate();
};

class GreaterEqulNode : public BinaryOperatorNode {
	public:
		GreaterEqulNode(ExpressionNode *l, ExpressionNode *r);
		virtual int Evaluate();
};

class EqulNode : public BinaryOperatorNode {
	public:
		EqulNode(ExpressionNode *l, ExpressionNode *r);
		virtual int Evaluate();
};

class NotEqulNode : public BinaryOperatorNode {
	public:
		NotEqulNode(ExpressionNode *l, ExpressionNode *r);
		virtual int Evaluate();
};

class OrNode : public BinaryOperatorNode {
	public:
		OrNode(ExpressionNode *l, ExpressionNode *r);
		virtual int Evaluate();
};

class AndNode : public BinaryOperatorNode {
	public:
		AndNode(ExpressionNode *l, ExpressionNode *r);
		virtual int Evaluate();
};

class IntegerNode : public ExpressionNode {
	public:
		IntegerNode(int i);
		int Evaluate();
		int getNumber() {return number;}
	private:
		int number;
};

class IdentifierNode : public ExpressionNode {
    public:
		IdentifierNode(string,VariableList* vl);
		string  getName() {return name;}
		void    setNumber(int );
		int     Evaluate(); 
    private:
		string name;
		VariableList* vl;
};

class EndlNode : public ExpressionNode{
    public:
		EndlNode() {}
		int Evaluate();
};