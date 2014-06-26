#include<iostream>
#include<string>
#include"Parser.h"


using namespace std;


int main()
{
	cout<<"Inpunt your txt.file please"<<endl;
	string file;
	cin>>file;
	cout<<endl;
	Scanner s(file);
	s.startScan();
	VariableList vl;
	Parser p=Parser(&s,&vl);
	s.printTokens(); //for debugging!
	p.start()->Interpret();

	return 0;
}
