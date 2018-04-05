#include <iostream>
#include <stack>
#include <vector>
#include <map>

class ArithmeticExpression;
class BooleanExpression;
class Command;


struct Line { //has-a relationship with Command

    int value; //unsigned
    Command* c;
    Line(int v, Command* _c) {value = v, c = _c;}
};

class Program {
public:
	//friend class Command;
	//friend class LetVar;
	//takes in a pointer to a stack for gosub, map for all Variables, 
	//map for all Variable Arrays
	Program(); 
	~Program();

	//adding a line
	void addLine(int x, Command* c);

	//adding a variable array
	void addArray();

	//adding a Variable -- make sure to check if variable already exists
	void addVariable(std::string name, int x);

	//adding a GoSub
	void addGoSub(Line*);

	//testing if GoSub empty
	bool GoSubEmpty();

	//get most recent GoSub
	Line* getGoSub();

	//removing a GoSub from the stack
	void removeGoSub();

	//current index in allLines
	static unsigned int itAllLines;

	//initialize vector of all lines
	//static
	static std::vector<Line*> allLines;
	//initialize map of all lines
	//map of lines for efficient IfThen, GoTo, GoSub
	static std::map<int, Command*> linejump; //int is the line#
	//stack of GOSUB calls - stack of pointers to line objects
	//that store GoSuB objects
	static std::stack<Line*> allGoSub;

	//map of Variables - the key is the name, the value is an evaluated Variable object
	static std::map<std::string, int> allVariables;

	//map of variable arrays - key is the name, value is a pointer to a variable array object
	static std::map<std::string, std::map<int, int>* > allArrays;

}; 