#include"Parser.h"

using namespace std;


Token Parser::match(string expectedToken){
	Token current = mScanner->nextToken();
	if(current.getTokenType() != expectedToken) {
		cout <<"Error: Line "<<current.getLineNumber()<<"  Expected token type  "<<expectedToken<<endl;
		cout<<"your input is  "<<current.getLexeme()<<endl;//for debugging
	}
	return current;
}

StartNode* Parser::start(){
	while(mScanner->peekToken().getTokenType()=="COMMENT"){
	match("COMMENT");
	}
	match("INT");
	match("MAIN");
	match("LEFTPAREN");
	match("RIGHTPAREN");
	match("LEFTBRACE");
	StatementGroupNode* mSgNode=parseStatementGroupNode();
	StartNode * sn = new StartNode(mSgNode);
	match("RIGHTBRACE");
	return sn;
}

StatementGroupNode* Parser::parseStatementGroupNode(){
	StatementGroupNode* sg=new StatementGroupNode();
	while(true){
		StatementNode* sn=parseStatement();
		if(sn==NULL)
			break;
		sg->AddStatement(sn);
	}
	return sg;
}

StatementNode* Parser::parseStatement(){
	StatementNode* sn=NULL;
	string TokenType;
	TokenType=mScanner->peekToken().getTokenType();
        if(TokenType=="COUT"){
		    sn=parserCout();
	    }
		else if(TokenType=="INT"){
			sn=parseDeclaration();
			//mVl->printVariables();//for debugging!
		}
		else if(TokenType=="IDENTIFIER"){
			sn=parseAssignment();
		}
		else if(TokenType=="IF"){
			sn=parseIf();
		}
		else  if(TokenType=="WHILE"){
			sn=parseWhile();
		}
		else if(TokenType=="RIGHTBRACE")
			;
		else{
		cout<<"Error: expect Token Type: Cout or Int or Identifier or If or While";
		}
	return sn;
}

StatementNode* Parser::parserCout(){
	match("COUT");
	match("INSERTION");
	CoutStatementNode* sn=new CoutStatementNode();
	ExpressionNode* en=NULL;
	while(true){
		en=parseExpression();
		sn->addExpression(en);
		if(mScanner->peekToken().getTokenType()=="SEMICOLON" || en==NULL){
			break;
		}
	}
	//cout<<sn->getCVector().size()<<endl; //for debugging!
	//if(en!=NULL) cout<<en->Evaluate();//for debugging!
	match("SEMICOLON");
	return sn;
}

StatementNode* Parser::parseDeclaration(){
	match("INT");
	IdentifierNode* in=parseIdentifier();
	mVl->addVariable(in->getName());
	DeclarationStatementNode* dn=new DeclarationStatementNode(in);
	match("SEMICOLON");
	return dn;
}

StatementNode* Parser::parseAssignment(){
	IdentifierNode* in=parseIdentifier();
	ExpressionNode* en=NULL;
	string TokenType=mScanner->peekToken().getTokenType();
	if(TokenType=="ASSIGN"){
		match("ASSIGN");
		en=parseExpression();
		match("SEMICOLON");
		AssignmentStatementNode* an=new AssignmentStatementNode(in,en);
		return an;
	}
	else if(TokenType=="PLUSASSIGN"){
		match("PLUSASSIGN");
		en=parseExpression();
		match("SEMICOLON");
		PlusAssignNode* pn=new PlusAssignNode(in,en);
		return pn;
	}
	else if(TokenType=="MINUSASSIGN"){
		match("MINUSASSIGN");
		en=parseExpression();
		match("SEMICOLON");
		MinusAssignNode* mn=new MinusAssignNode(in,en);
		return mn;
	}
	else{
		cout<<"Error:expect Token Assign or PlusAssign or MinusAssign"<<endl;
	}
	return NULL;
}

IfStatementNode* Parser::parseIf(){
	match("IF");
	match("LEFTPAREN");
	ExpressionNode* en=parseExpression();
	match("RIGHTPAREN");
	StatementNode* sn=parseStatement();
	if(en==NULL || sn==NULL){
		cout<<"Error: IF statement NULL pointer!";
		return NULL;
	}
	IfStatementNode* in=new IfStatementNode(en,sn);
	return in;
}

WhileStatementNode* Parser::parseWhile(){
	match("WHILE");
	match("LEFTPAREN");
	ExpressionNode* en=parseExpression();
	match("RIGHTPAREN");
	StatementNode* sn=parseStatement();
	if(en==NULL || sn==NULL){
		cout<<"Error: WHILE statement NULL pointer!";
		return NULL;
	}
	WhileStatementNode* in=new WhileStatementNode(en,sn);
	return in;
}

ExpressionNode* Parser::parseExpression(){
	ExpressionNode* en=parseOr();
	return en;
}

IntegerNode* Parser::parseInteger(){
     Token current=match("INTEGER");
	 int number=atoi(current.getLexeme().c_str());
	 IntegerNode* in=new IntegerNode(number);
	 return in;
}

IdentifierNode* Parser::parseIdentifier(){
	 Token t=match("IDENTIFIER");
	 string name=t.getLexeme();
	 IdentifierNode* in=new IdentifierNode(name,mVl);
	 return in;
}

ExpressionNode* Parser::parseOr(){
	 ExpressionNode* en=parseAnd();
	 if(en==NULL) return NULL;
	 ExpressionNode* en1;
	 string TokenType=mScanner->peekToken().getTokenType();
	 if(TokenType=="OR"){
		match("OR");
		en1=parseLogical();
		if(en1==NULL) 
			return NULL;
		else
		    en=new OrNode(en,en1);
	 }
	 return en;
}

ExpressionNode* Parser::parseAnd(){
	 ExpressionNode* en=parseLogical();
	 if(en==NULL) return NULL;
	 ExpressionNode* en1;
	 string TokenType=mScanner->peekToken().getTokenType();
	 if(TokenType=="AND"){
		match("AND");
		en1=parseOr();
		if(en1==NULL) 
			return NULL;
		else
		    en=new AndNode(en,en1);
	 }
	 return en;
}

ExpressionNode* Parser::parseLogical(){
	ExpressionNode* en=addAndMin();
	if(en==NULL) return NULL;
	ExpressionNode* en1;
	string TokenType=mScanner->peekToken().getTokenType();
	if(TokenType=="LESS"){
		match("LESS");
		en1=addAndMin();
		if(en1==NULL) 
			return NULL;
		else
		    en=new LessNode(en,en1);
	}
	else if(TokenType=="LESSEQUL"){
		match("LESSEQUL");
		en1=addAndMin();
		if(en1==NULL) 
			return NULL;
		else
		    en=new LessEqulNode(en,en1);
	}
	else if(TokenType=="GREATER"){
		match("GREATER");
		en1=addAndMin();
		if(en1==NULL) 
			return NULL;
		else
		    en=new GreaterNode(en,en1);
	}
	else if(TokenType=="GREATEQUL"){
		match("GREATEQUL");
		en1=addAndMin();
		if(en1==NULL) 
			return NULL;
		else
		    en=new GreaterEqulNode(en,en1);
	}
	else if(TokenType=="EQUL"){
	    match("EQUL");
		en1=addAndMin();
		if(en1==NULL) 
			return NULL;
		else
		    en=new EqulNode(en,en1);
	}
	else if(TokenType=="NOTEQUL"){
		match("NOTEQUL");
		en1=addAndMin();
		if(en1==NULL) 
			return NULL;
		else
		    en=new NotEqulNode(en,en1);
	}

	return en;
}

ExpressionNode* Parser::addAndMin(){
     ExpressionNode* en=mutAndDiv();
	 if(en==NULL) return NULL;
	 ExpressionNode* en1;
	 string TokenType;
	 while(true){
		 TokenType=mScanner->peekToken().getTokenType();
	     if(TokenType=="PLUS" && (en!=NULL)){
		    match("PLUS");
			en1=mutAndDiv();
			if(en1==NULL) 
				return NULL;
			else
		        en=new PlusNode(en,en1);
	     }
	     else if(TokenType=="MINUS" && (en!=NULL)){
		    match("MINUS");
			en1=mutAndDiv();
			if(en1==NULL) 
				return NULL;
			else
		        en=new MinusNode(en,en1);
	     }
		 else
			break;
	 }
	 return en;
}

ExpressionNode* Parser::mutAndDiv(){
	 ExpressionNode* en=parseToken();
	 if(en==NULL) return NULL;
	 ExpressionNode* en1;
	 string TokenType;
	 while(true){
		TokenType=mScanner->peekToken().getTokenType();
	    if(TokenType=="MUTIPLY" && (en!=NULL)){
		   match("MUTIPLY");
		   en1=parseToken();
		   if(en1==NULL) 
			   return NULL;
		   else
		       en=new MutiNode(en,en1);
	    }
	    else if(TokenType=="DIVID" && (en!=NULL)){
		   match("DIVID");
		   en1=parseToken();
		   if(en1==NULL) 
			   return NULL;
		   else
		       en=new DiviNode(en,en1);
	    }
		else if(TokenType=="MOD" && (en!=NULL)){
           match("MOD");
		   en1=parseToken();
		   if(en1==NULL) 
			   return NULL;
		   else
		       en=new ModNode(en,en1);
		}
		else
			break;
	 }
	 return en;
}

ExpressionNode* Parser::parseToken(){
	 ExpressionNode* en=NULL; 
	 string TokenType=mScanner->peekToken().getTokenType();
	 if(TokenType=="INTEGER"){
		 en=parseInteger();
	 }
	 else if(TokenType=="LEFTPAREN"){
		 match("LEFTPAREN");
		 en=parseExpression();
		 match("RIGHTPAREN");
	 }
	 else if(TokenType=="ENDL"){
		 match("ENDL");
	 }
	 else if(TokenType=="IDENTIFIER"){
		 en=parseIdentifier();
	 }
	 else{
		 cout<<"Error:expect Token Type: INTEGER or IDENTIFIER or (  or endl"<<endl;
	 }
	 return en;
}