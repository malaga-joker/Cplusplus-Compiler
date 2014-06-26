#include"Scanner.h"
#include<fstream>
#include<sstream>


using namespace std;

char T_special[8]={'+','-','=','>','<','!','&','|'};


bool Reader:: finishRead()
{
  if(CurrPos==(DataLength))
	  return true;
  else
	  return false;
}

 void Reader::retract()
 {
  if(CurrPos<=0)
	  CurrPos=0;
  else
	  CurrPos-=1;
 }

 Reader:: Reader(string str)
{
  data=str;
  CurrPos=0;
  DataLength=str.length();
}

char Reader::NextChar()
{
  if(CurrPos>DataLength)
	  return -1;

  return data[CurrPos++];
}

Token Scanner::peekToken(){
	    int flag1=reader.getCurrPos();
		int count=currLine;
	    Token peek=nextToken();
		while(peek.getTokenType()=="COMMENT"){
			flag1=reader.getCurrPos();
			count=currLine;
			peek=nextToken();
		}
		int flag2=reader.getCurrPos();
		for(int i=0;i<(flag2-flag1);i++){
		   reader.retract();
		}
		currLine=count;
		return peek;
}

Token Scanner::nextToken(){
        char c=reader.NextChar();

		while(c==' ' || c=='\n' || c=='\r'){
			if(c=='\n'){
				currLine++;
			}
			c=reader.NextChar();
		}
		
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{ 
			state=2;
			reader.retract();
			return nextToken_identifier();
	    }
		else if(static_cast<int>(c)>=48 && static_cast<int>(c)<=57)
		{
		    state=3;
			reader.retract();
			return nextToken_number(); 
		}
		else if(special(c))
		{
			state=5;
		    reader.retract();
			return nextToken_special();
		}
		else if(c=='/')
		{  
            char c=reader.NextChar();
		    if(c=='*')
		    {
			   state=4;
			   return nextToken_comment();
		    }
		    else
			{
				   state=1;
		           reader.retract();
				   reader.retract();
				   return nextToken_single(); 
		    }
		}
		else
	    {
		   state=1;
		   reader.retract();
		   return nextToken_single(); 
	    }
}

Token Scanner:: nextToken_special()
{
	      char c=reader.NextChar();
		  char d;
			     switch(c)
			    {
			        case '+':
					d=reader.NextChar();
						if(d=='+') {
							Token t=Token("PLUSPLUS","++",currLine);
							return t;}
						else if(d=='=') {
							Token t=Token("PLUSASSIGN","+=",currLine);
							return t;}
						else 
						{
						    reader.retract();
							Token t=Token("PLUS","+",currLine);
							return t;
						}
                    break;
					case '-':
                        d=reader.NextChar();
						if(d=='-') {
							Token t("MINUSMINUS","--",currLine);
							return (t);}
						else if(d=='=') {
							Token t("MINUSASSIGN","-=",currLine);
							return (t);}
						else 
						{
						    reader.retract();
							Token t("MINUS","-",currLine);
							return (t);
						}
                    break;
                    case '=':
                        d=reader.NextChar();
					    if(d=='=') {
							Token t("EQUL","==",currLine);
							return (t);}
						else
						{
						    reader.retract();
							Token t("ASSIGN","=",currLine);
							return (t);
						}
                    break;
                    case '>':
                        d=reader.NextChar();
					    if(d=='=') {
							Token t("GREATEQUL",">=",currLine);
							return (t);}
						else
						{
						    reader.retract();
							Token t("GREATER",">",currLine);
							return (t);
						}
                    break;
                    case '<':
                        d=reader.NextChar();
					    if(d=='=') {
							Token t("LESSEQUL","<=",currLine);
							return (t);}
						else if(d=='<'){
						     Token t=Token("INSERTION","<<",currLine);
							 return t;
					    }
						else
						{
						    reader.retract();
							Token t("LESS","<",currLine);
							return (t);
						}
                    break;
                    case '!':
                        d=reader.NextChar();
					    if(d=='=') {
							Token t("NOTEQUL","!=",currLine);
							return (t);}
						else
						{
						    reader.retract();
						}
                    break;
                    case '&':
                        d=reader.NextChar();
					    if(d=='&') {
							Token t("AND","&&",currLine);
							return (t);}
						else
						    reader.retract();
                    break;
					case '|':
                        d=reader.NextChar();
					    if(d=='|') {
							Token t("OR","||",currLine);
							return (t);}
						else
						    reader.retract();
                    break;
			      }
				return Token(); 
}

Token Scanner:: nextToken_number()
{
         string bufferStr;

		 while(state==3)
	    {
			char c=reader.NextChar();
		    if(static_cast<int>(c)>=48 && static_cast<int>(c)<=57) 
					bufferStr+=c;
			else
	       {
			  reader.retract();
			  break;
		   }
	    }
		     Token t=Token("INTEGER",bufferStr,currLine);
			 return t;
}

Token Scanner::nextToken_single()
	{
		   while(true)
		   {
		     char c=reader.NextChar();
			
			        if(c==':'){
						Token t=Token("COLON",":",currLine);
						return t;
					}
					else if(c==';'){
						Token t=Token("SEMICOLON",";",currLine);
						return t;
					}
					else if(c=='('){
						Token t=Token("LEFTPAREN","(",currLine);
						return t;
					}
					else if(c==')'){
						Token t=Token("RIGHTPAREN",")",currLine);
						return t;
					}
					else if(c=='{'){
						Token t=Token("LEFTBRACE","{",currLine);
						return t;
					}
					else if(c=='}'){
						Token t=Token("RIGHTBRACE","}",currLine);
						return t;
					}
					else if(c=='%'){
						Token t=Token("MOD","%",currLine);
						return t;
					}
					else if(c=='/'){
						Token t=Token("DIVID","/",currLine);
						return t;
					}
					else if(c=='*'){
						Token t=Token("MUTIPLY","*",currLine);
						return t;
					}
					else if(c==EOF){
						Token t=Token("EOF","eof",currLine);
					}
					else{
						string str="undefined symbol ";
						str+=c;
						return Token("UNDEFINED",str,currLine);
					}
		     }
		}

Token Scanner::nextToken_identifier()
{
	         string bufferStr;

			 while(state==2)
			 {
			    char c=reader.NextChar();
		        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 
					bufferStr+=c;
				else
				{
				 reader.retract();
				 break;
				}
			 }
			 if(bufferStr=="int"){
				 Token t=Token("INT","int",currLine);
				 return t;}
			 else if(bufferStr=="if"){
				 Token t=Token("IF","if",currLine);
				 return t;}
			 else if(bufferStr=="while"){
				 Token t=Token("WHILE","while",currLine);
				 return t;}
			 else if(bufferStr=="cout"){
				 Token t=Token("COUT","cout",currLine);
				 return t;}
			 else if(bufferStr=="endl"){
				 Token t=Token("ENDL","endl",currLine);
				 return t;}
			 else if(bufferStr=="void"){
				 Token t=Token("VOID","void",currLine);
				 return t;}
			 else if(bufferStr=="main"){
				 Token t=Token("MAIN","main",currLine);
				 return t;}
			  else if(bufferStr=="return"){
				 Token t=Token("RETURN","return",currLine);
				 return t;}
			 else{
				 Token t=Token("IDENTIFIER",bufferStr,currLine);
				 return t;}
}

Token  Scanner::nextToken_comment()
{
	      int count=0;
		    while(state==4)
		  {
             if(count>100){
				 cout<<"Error: the limit input for a comment is 100! Please check your comment "<<endl;
				 break;
			 }
			 char c=reader.NextChar();
			 if(c=='*'){
				 c=reader.NextChar();
				 if(c=='/') 
					 break;
				 else 
					 reader.retract();
			 }
			 else if(c=='\n'){
				 currLine++;
			 }
			 count++;
		  }
			Token t=Token("COMMENT","comment",currLine);
			return t;
}

bool  Scanner::special(char c)
{
    for(int i=0;i<8;i++)
	{
	  if(T_special[i]==c)
		  return true;
	}
	return false;
}

void Scanner::printTokens()
{
	while(!reader.finishRead())
	{
	  cout<<nextToken()<<endl;
	}
}

void Scanner::startScan()
{
	string total;
	char c;
    fstream infile(file);
	if ( infile.fail() ) 
	{
      cout << "Input file openning failed" << endl;
      return;
    }

    while(!infile.eof())
   {
	   infile.get(c);
	   total+=c;
   }

	while((int)total[total.size()-1]== 10)
	{
	   total=total.substr(0,total.size()-1);
	}
	infile.close();
	read(total);
}


ostream& operator<<(ostream& out, Token & tc) {
	return out << tc.getTokenType() <<"   "<< tc.getLexeme()<<"    "<<tc.getLineNumber();
}