#include<iostream>
#include"VariableList.h"

using namespace std;


ostream& operator<<(ostream& out, Variable & va){
	return out<<va.getName()<<"  "<<va.getNumber()<<"          ";
}

bool VariableList::checkVariable(string str){
	for(int i=0;i<(signed)list.size();i++){
		if(str==list[i].getName()){
			cout<<"Error:the Idantifier "<<str<<" has already been declared!"<<endl;
			return false;
		}
	}
	return true;
}

bool VariableList::exist(string str){
	for(int i=0;i<(signed)list.size();i++){
		if(str==list[i].getName()){
			return true;
		}
	}
	return false;
}

void VariableList::addVariable(string str){
	if(!checkVariable(str))
		;
	else
		list.push_back(Variable(str));
}

Variable VariableList::getVariable(string str){
	Variable v;
    for(int i=0;i<(signed)list.size();i++){
		if(str==list[i].getName()){
			v=list[i];
			break;
		}
	}
	return v;
}

int VariableList::getNumber(string str){
	if(exist(str)){
	   int number;
	   for(int i=0;i<(signed)list.size();i++){
		   if(str==list[i].getName()){
			  number=list[i].getNumber();
			  break;
		   }
	   }
	   return number;
	}
	else{
		cout<<"The variable "<<str<<" is undefined!"<<endl;
		return 0;
	}
}

void VariableList::setNumber(string str,int number){
	for(int i=0;i<(signed)list.size();i++){
		if(str==list[i].getName()){
			list[i].setNumber(number);
			return;
		}
	}
}

void VariableList::printVariables(){
	for(int i=0;i<(signed)list.size();i++){
		cout<<list[i];
	}
	cout<<endl;
}