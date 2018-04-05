#include "Program.h"


unsigned int Program::itAllLines;

std::vector<Line*> Program::allLines;

std::map<int, Command*> Program::linejump;

std::stack<Line*> Program::allGoSub;

std::map<std::string, int> Program::allVariables;

std::map<std::string, std::map<int, int>* > Program::allArrays;


//implement Program class
Program::Program() {
	Program::itAllLines = 0;
}

Program::~Program() {
	/*
	for (unsigned int i=0; i < Program::allLines.size(); i++) {
		delete Program::allLines[i] -> c;
		delete Program::allLines[i];
	}
	*/
}

void Program::addLine(int x, Command* _c) {
	//add command to vector "allLines" and map "linejump"
    Line* new_line = new Line(x, _c);
    Program::allLines.push_back(new_line);
    linejump[x] = _c;
}

//adding Variable array
void Program::addArray() {
	//adding to the map of all variable arrays,
	//where the key is the name and the value is a pointer
	//to an ArithmeticExpression, which is a VarArray
}

//adding a Variable
void Program::addVariable(std::string s, int x) {
	//adding to a map
	//how to insert to a map?
	//int x = ae->evaluate();
	std::map<std::string, int>::iterator it = Program::allVariables.find(s);
	if (it != Program::allVariables.end()) { //if pos already key in map 
		it->second = x;

	}
	else { //pos not key in map -- insert pair
		//vararray->insert(pos, value);
		//overwrite
		Program::allVariables[s] = x;
	}

}

//adding a GoSub
void Program::addGoSub(Line* l) {
	Program::allGoSub.push(l);
}

//testing if GoSub empty
bool Program::GoSubEmpty() {
	return Program::allGoSub.empty();
}

Line* Program::getGoSub() {
	//if (GoSubEmpty()) {throw Error("No matching GOSUB for RETURN.");}
	return Program::allGoSub.top();
}

//removing a GoSub from the stack
void Program::removeGoSub() {
	Program::allGoSub.pop();
}