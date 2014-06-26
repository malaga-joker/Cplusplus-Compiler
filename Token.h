#include<string>

using namespace std;



class Token{

private:
	     string tokenType;
		 string lexeme;
		 int    lineNumber;

public:
	     Token() {}
		 Token(string tokenType,string lexeme,int lineNumber) {this->tokenType=tokenType; this->lexeme=lexeme; this->lineNumber=lineNumber;}
		 string getTokenType()    {return tokenType;}
		 string getLexeme()       {return lexeme;}
		 int    getLineNumber()   {return lineNumber;}
};

