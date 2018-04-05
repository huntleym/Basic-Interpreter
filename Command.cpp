#include "Program.h"
#include "ArithmeticExpression.h"
#include "BooleanExpression.h"
#include "Command.h"



//PRINT just evaluates _ae and prints it
Print::Print(ArithmeticExpression *ae) {
	_ae = ae;
}

Print::~Print() {
	delete _ae;
}

void Print::print(std::ostream & o) const {
    o << "PRINT ";
    _ae->print(o);
}

void Print::fullprint() {
	std::cout << _ae->evaluate() << std::endl;
}

void Print::execute() {
	std::cout << _ae->evaluate() << std::endl;
}


//LET VAR stores an evaluated AE into a Var
LetVar::LetVar(Variable *v, ArithmeticExpression *ae) {
	_ae = ae;
	_var = v; 
}

LetVar::~LetVar() {
	delete _ae;
	delete _var;
}

void LetVar::print(std::ostream & o) const {
	o << "LET ";
	_var->print(o);
	o << " ";
	_ae->print(o);
}

void LetVar::execute() {
	//we need to add the variable to allVariables/overwrite it
	int y = _ae->evaluate();
	//we need to take _var and write x into it

	//we need to search through allVariables

	std::string name = _var->getName();
	
	//add to map allVariables
	std::map<std::string, int>::iterator it = Program::allVariables.find(name);
	if (it != Program::allVariables.end()) { //if pos already key in map 
		it->second = y;
	}
	else { //pos not key in map -- insert pair
		Program::allVariables[name] = y;

	}
	
}


//for LET for var arrays
LetVarArray::LetVarArray(VarArray *v, ArithmeticExpression *ae) {
	varA = v;
	_ae = ae;
}

LetVarArray::~LetVarArray() {
	delete varA;
	delete _ae;
}

void LetVarArray::print(std::ostream & o) const {
	o << "LET ";
	varA->print(o);
	o << " ";
	_ae->print(o);
}

void LetVarArray::execute() {
	//find var array in Program::allArrays
	
	std::string name = varA->getName();
	ArithmeticExpression* inner = varA->getInner();
	/*
	(*Program::allArrays[name])[inner->evaluate()] = _ae->evaluate();
	*/

	std::map<std::string, std::map<int, int>* >::iterator it = Program::allArrays.find(name);
	if (it != Program::allArrays.end()) { //if varArray already key in map 
		//now we have to iterate through the map<int, int> in allArrays
		//first, see if already in map<int, int>
		std::map<int, int>::iterator it2 = it->second->find(inner->evaluate());
		if (it2 != it->second->end()) { //if already key in map
			it2->second = _ae->evaluate();
		}
		else {
			(*it->second)[inner->evaluate()] = _ae->evaluate();

		}

	}
	else { //Array not in map -- insert pair
		std::map<int, int>* thatArray = new std::map<int, int>;
		Program::allArrays[name] = thatArray;

		//we know that the int, int pair is not in thatArray, since the array 
		//has not been initialized
		(*thatArray)[inner->evaluate()] = _ae->evaluate(); 

	}
		
}

//GOTO
GoTo::GoTo(int l) {
	line = l;
}

GoTo::~GoTo() {
}

void GoTo::print(std::ostream & o) const {
	std::cout << "GOTO " << "<" << line << ">";
}

int GoTo::getLine() const {
	return line;
}

void GoTo::execute() {
	//change Program::itAllLines

	//first check if line is valid
	std::map<int, Command*>::iterator it = Program::linejump.find(line);
	if (it == Program::linejump.end()) { //if line not existent 
		int linej = Program::allLines[Program::itAllLines] -> value;

		throw Error("GOTO to non-existent line <", linej, line);

	}


	for (unsigned int i = 0; i<Program::allLines.size(); i++) {
		if (Program::allLines[i] -> value == line) {
			Program::itAllLines = i-1; //b/c the for loop in Program will increment i
			break;
		} 
	}
	
}

//IFTHEN
IfThen::IfThen(BooleanExpression *be, int l) {
	_be = be;
	_linej = l;
}

IfThen::~IfThen() {
	delete _be;
}

void IfThen::print(std::ostream & o) const {
	o << "IF ";
	_be->print(o);
	o << " THEN " << "<" << _linej << ">";
}

int IfThen::getLine() const {
	return _linej;
}

void IfThen::execute() {
	//evaluate the boolean expression and change the current line number
	if (_be->evaluate()) {

		std::map<int, Command*>::iterator it = Program::linejump.find(_linej);
		if (it == Program::linejump.end()) { //if line not existent 
			int line = Program::allLines[Program::itAllLines] -> value;

			throw Error("IFTHEN to non-existent line <", line,_linej);

		}

		for (unsigned int i = 0; i<Program::allLines.size(); i++) {
			if (Program::allLines[i] -> value == _linej) {
				Program::itAllLines = i-1; //b/c the for loop in Program will increment i
				break;
			}
		}
		
	}
	
}

//GOSUB calls GOTO and stores the line it came from
GoSub::GoSub(int lgo, int lfrom) {
	linej = lgo;
	linefrom = lfrom;
}

GoSub::~GoSub() {
}

void GoSub::print(std::ostream & o) const {
	o << "GOSUB " << "<" << linej << ">";
}

void GoSub::execute() {
	//add a GoSub to the stack with line from

	//if linej is nonexistent, then throw exception
	std::map<int, Command*>::iterator it = Program::linejump.find(linej);
	if (it == Program::linejump.end()) { //if line not existent 
		int line = Program::allLines[Program::itAllLines] -> value;

		throw Error("GOSUB to non-existent line <", line, linej);
	}

	//creates new Line gosub object
	Line* line = new Line(linefrom, this);

	//pushes it to allGoSub
	Program::allGoSub.push(line);

	//jumps to linej by changing the interator i in Program

	//find the linej in the map of all lines -- unnecessary b/c
	//we have to iterate through the vector anyways
	//std::map<int, Command*>::iterator it = linejump.find(linej);
	for (unsigned int i = 0; i<Program::allLines.size(); i++) {
		if (Program::allLines[i] -> value == linej) {
			Program::itAllLines = i-1; //b/c the for loop in Program will increment i
			break;
		}
	}
	
}

//RETURN calls GOTO on the line after the last GoSub
Return::Return() {
	//nothing here yet
}

Return::~Return() {
	//nothing here yet
}

void Return::print(std::ostream & o) const {
	o << "RETURN";
}

void Return::execute() {
	//goes to the line after the last GoSub 

	//if GoSub stack empty, throw error
	if (Program::allGoSub.empty()) {
		//find current line
		int line = Program::allLines[Program::itAllLines] -> value;
		throw Error("No matching GOSUB for RETURN.", line);
	}

	//pulls the last GoSub from the stack
	Line* last = Program::allGoSub.top();

	//loops through all lines for that line and changes the iterator
	for (unsigned int i = 0; i<Program::allLines.size(); i++) {
		if (Program::allLines[i] -> value == last->value) {
			Program::itAllLines = i; //b/c the for loop in Program will increment i
			break;
		}
	}

	//pops that GoSub from the stack
	Program::allGoSub.pop();
}


//END just terminates to program right then and there
End::End() {
	//nothing
}

End::~End() {
	//nothing
}

void End::print(std::ostream & o) const {
	o << "END";
}

void End::execute() {
	//throw error with empty string to terminate program
	throw Error("");
}