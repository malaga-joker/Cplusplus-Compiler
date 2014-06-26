#include<vector>
#include<string>

using namespace std;

struct Variable{
                    private:    
	                          string name;
	                          int    number;
                    public:
						Variable() {}
						Variable(string str) {this->name=str;this->number=0;}
						string getName() {return name;} 
						int    getNumber() {return number;}
						void   setNumber(int number) {this->number=number;}
			 };
ostream& operator<<(ostream& out, Variable & va);

class VariableList{

    private:
		     
		     vector<Variable> list;
		
     public:
		              VariableList() {}	  
		     bool     checkVariable(string );
			 bool     exist(string );
			 void     addVariable(string );
			 Variable getVariable(string );
			 int      getNumber(string );
			 void     setNumber(string ,int);
			 void     printVariables();
};

