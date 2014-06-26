#include<iostream>
#include<string>
#include<vector>
#include"Token.h"
using namespace std;

class Reader
{
private:
	     string data;
		 int    CurrPos;
		 int    DataLength;

public:
	     Reader() {}
		 Reader(string);
		 int  getCurrPos() {return CurrPos;}
		 char NextChar();
		 void retract();
		 bool finishRead();
		 int  gerlen() {return DataLength;}
};




class Scanner
{
private:
	     Reader reader;
		 int    currLine;
		 int    state;
		 string file;

public:
	    Scanner(string str) {currLine=1; state=1; reader=Reader();file=str;}

		int    getcurrLine()     {return currLine;}

		void read(string str) {state=1; reader=Reader(str); }

		Token nextToken();

		Token peekToken();

		Token nextToken_number();
		
		Token nextToken_single();	

		Token nextToken_identifier();

		Token nextToken_comment();

		Token nextToken_special();

		bool   special(char);

		void   printTokens();

		void   startScan();
};


ostream& operator<<(ostream& out, Token & tc);