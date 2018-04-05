#include "Program.h"
#include "ArithmeticExpression.h"



//division by zero constructor
Error::Error(int line, std::string m, ArithmeticExpression* _ae1, ArithmeticExpression* _ae2) {
	lineat = line;
	message = m;
	ae1 = _ae1;
	ae2 = _ae2;
}

//GoTo, IfThen, GoSub contructor 
Error::Error(std::string s, int line, int linej) {
	message = s;
	lineat = line;
	linenot = linej;
}

//no previous GoSub constructor
Error::Error(std::string s, int line) {
	message = s;
	lineat = line;
}

//miscellaneous error
Error::Error(std::string s) { 
	message = s;
}

Error::~Error() {

}

void Error::what() {
	
	if (message == "Division by 0") {
		//do something for division by zero
		std::cout << "Error in Line " << lineat << ": ";
		std::cout << message << ": ";
		ae1->print(std::cout);
		std::cout << " = " << ae1->evaluate() << ", ";
		ae2->print(std::cout);
		std::cout << " = " << ae2->evaluate() << "." << std::endl;
	}
	else if (message == "GOTO to non-existent line <") {
		std::cout << "Error in Line " << lineat << ": ";
		std::cout << message << linenot << ">." << std::endl;
	}

	else if (message == "IFTHEN to non-existent line <") {
		std::cout << "Error in Line " << lineat << ": ";
		std::cout << message << linenot << ">." << std::endl;
	}

	else if (message == "GOSUB to non-existent line <") {
		std::cout << "Error in Line " << lineat << ": ";
		std::cout << message << linenot << ">." << std::endl;
	}

	else if (message == "No matching GOSUB for RETURN.") {
		std::cout << "Error in Line " << lineat << ": ";
		std::cout << message << std::endl;
	}
	std::cout << std::endl;
	
}


//implementation for Constant class
Constant::Constant(int x) {
	value = x;
}

Constant::~Constant() {

}

void Constant::print(std::ostream & o) const {
    o << value;
}

int Constant::evaluate() {
	return value;
}

std::string Constant::getName() {
	return std::to_string(value);
}

//implementation for Variable class
Variable::Variable(std::string s) {
	name = s;
	value = 0; //is zero as default
}

Variable::~Variable() {

}

void Variable::print(std::ostream & o) const {
    o << name;
}

void Variable::initialize(std::map<std::string, int>* allvars) {
	//iterate through allvars and find the real value of the variable
	std::map<std::string, int>::iterator it = allvars->find(name);
	if (it != allvars->end()) { //if variable is in map 
		value = it->second;
		//std::cout << value << std::endl;
	}

}

int Variable::evaluate() {
	//std::cout << value << std::endl;

	//first we have to find if Variable already in Program allVariables
	std::map<std::string, int>::iterator it = Program::allVariables.find(name);
	if (it != Program::allVariables.end()) { //if variable is in map 
		value = it->second;
		//std::cout << value << std::endl;
	}

	return value;
}

std::string Variable::getName() {
	return name;
}

//implementation for VarArray class
VarArray::VarArray(std::string s, ArithmeticExpression *ae) {
	name = s;
	inner = ae;
	//vararray = new std::map<int, int>;
}

VarArray::~VarArray() {
	if (inner != NULL) {delete inner;}
}

void VarArray::print(std::ostream & o) const {
	o << name << "[";
    inner->print(o);
    o << "]";
}

int VarArray::evaluate() { //which errors to check for?
	//find the value in Program::allArrays
	/*std::cout << "HERE" << std::endl;
	std::cout << Program::allArrays[name];

	std::cout << "HERE" << std::endl;

	return 0;*/
	
	std::map<std::string, std::map<int, int>* >::iterator it = Program::allArrays.find(name);

	if (it != Program::allArrays.end()) { //if varArray is key in map 
		//now we have to iterate through the map<int, int> in allArrays
		//first, see if already in map<int, int>
		std::map<int, int>::iterator it2 = it->second->find(inner->evaluate());
		if (it2 != it->second->end()) { //if is key in map
			//std::cout << it2->second << std::endl;
			return it2->second;
		}
	}
	return 0; //Array not in map -- return 0;
	
}

void VarArray::addValue(int pos, int value) { //pass in Arithmetic Expressions
	//pos and value are already-evaluated Arithmetic Expressions

	//how to insert to a map?
	std::map<int, int>::iterator it = vararray.find(pos);
	if (it != vararray.end()) { //if pos already key in map 
		it->second = value;

	}
	else { //pos not key in map -- insert pair
		//vararray->insert(pos, value);
		//overwrite
		vararray[pos] = value;
	}
}

std::string VarArray::getName() {
	return name;
}

ArithmeticExpression* VarArray::getInner() {
	return inner;
}

//implementation for Addition class
Addition::Addition (ArithmeticExpression *ae1, ArithmeticExpression *ae2)
{
  _ae1 = ae1;
  _ae2 = ae2;
}

Addition::~Addition ()
{
  if (_ae1 != NULL) {delete _ae1;}
  if (_ae2 != NULL) {delete _ae2;}
}
  
void Addition::print (std::ostream & o) const {
  o << "(";
  _ae1->print (o);
  o << " + ";
  _ae2->print (o);
  o << ")";
}

int Addition::evaluate() {
	int x = _ae1->evaluate();
	int y = _ae2->evaluate();
	return x + y;
}

std::string Addition::getName() {
	return "";

}

//implementation for Subtraction class
Subtraction::Subtraction (ArithmeticExpression *ae1, ArithmeticExpression *ae2) {
	this->ae1 = ae1;
	this->ae2 = ae2;
}

Subtraction::~Subtraction() {
	if (ae1 != NULL) {delete ae1;}
	if (ae2 != NULL) {delete ae2;}
}

void Subtraction::print (std::ostream & o) const {
	o << "(";
	ae1->print(o);
	o << " - ";
	ae2->print(o);
	o << ")";
}

int Subtraction::evaluate() {
	int x = ae1->evaluate();
	int y = ae2->evaluate();
	return x - y;	
}

std::string Subtraction::getName() {
	return "";

}

//implementation of Multiplication

Multiplication::Multiplication (ArithmeticExpression *ae1, ArithmeticExpression *ae2) {
	Ae1 = ae1;
	Ae2 = ae2;
}

Multiplication::~Multiplication() {
	if (Ae1 != NULL) {delete Ae1;}
	if (Ae2 != NULL) {delete Ae2;}
}

void Multiplication::print(std::ostream & o) const {
	o << "(";
	Ae1->print(o);
	o << " * ";
	Ae2->print(o);
	o << ")";
}

int Multiplication::evaluate() {
	int x = Ae1->evaluate();
	int y = Ae2->evaluate();
	return x * y;
	//return Ae1->evaluate() * Ae2->evaluate();
}

std::string Multiplication::getName() {
	return "";
}

Division::Division (ArithmeticExpression *ae1, ArithmeticExpression *ae2) {
	_Ae1 = ae1;
	_Ae2 = ae2;
}

Division::~Division() {
	if (_Ae1 != NULL) {delete _Ae1;}
	if (_Ae2 != NULL) {delete _Ae2;}
}

void Division::print(std::ostream & o) const {
	o << "(";
	_Ae1->print(o);
	o << " / ";
	_Ae2->print(o);
	o << ")";
}

int Division::evaluate() {
	//if (_Ae2->getvalue == 0) {throw logic_error("Division by O");}
	//should output error message, line # where happened, strings for
	//AE1 and AE2, and their values when the error happened
	//Make Error class, with Variable object as private member that holds
	//the error message
	int lhs = _Ae1->evaluate();
	int rhs = _Ae2->evaluate();

	//work on this
	if (rhs == 0) {
		//get line number from iterator in Program
		int line = Program::allLines[Program::itAllLines] -> value;

		throw Error(line, "Division by 0", _Ae1, _Ae2);
	}

	//put try-catch block in main
	//try {initialize Command object} catch (division_by_zero & e) {cout}
	return lhs/rhs;
}

std::string Division::getName() {
	return "";

}
