#include<iostream>
#include<string>
#include<vector>
#include"Scanner.h"
#include"Node.h"

using namespace std;


class Parser
{
   public:
	       Parser()   {}
		   Parser(Scanner* s,VariableList* vl)   {mScanner=s;mVl=vl;} 
		   StartNode* start();
		  
   private:
	       Token               match(string);
		   StatementGroupNode* parseStatementGroupNode();
		   StatementNode*      parseStatement();
		   StatementNode*      parserCout();
		   StatementNode*      parseDeclaration();
		   StatementNode*      parseAssignment();
		   ExpressionNode*     parseExpression();
		   ExpressionNode*     parseToken();
		   ExpressionNode*     mutAndDiv();
		   ExpressionNode*     addAndMin();
		   ExpressionNode*     parseLogical();
		   ExpressionNode*     parseOr();
		   ExpressionNode*     parseAnd();
		   IntegerNode*        parseInteger();   
		   IdentifierNode*     parseIdentifier();
		   IfStatementNode*    parseIf();
		   WhileStatementNode* parseWhile();


		   Scanner* mScanner;
		   VariableList* mVl;
};


 