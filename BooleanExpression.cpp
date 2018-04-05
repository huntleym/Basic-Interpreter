#include "ArithmeticExpression.h"
#include "BooleanExpression.h"

Equals::Equals(ArithmeticExpression *a1, ArithmeticExpression *a2) {
	this->_a1 = a1;
	this->_a2 = a2;
}

Equals::~Equals() {
	delete _a1;
	delete _a2;
}

void Equals::print(std::ostream & o) const {
	o << "[";
	_a1->print(o);
	o << " = ";
	_a2->print(o);
	o << "]";
}

bool Equals::evaluate() {
	if (_a1->evaluate() == _a2->evaluate()) {return true;}
	else {return false;}
}

GreaterThan::GreaterThan(ArithmeticExpression *a1, ArithmeticExpression *a2) {
	this->_A1 = a1;
	this->_A2 = a2;
}

GreaterThan::~GreaterThan() {
	delete _A1;
	delete _A2;
}

void GreaterThan::print(std::ostream & o) const {
	o << "[";
	_A2->print(o);
	o << " < ";
	_A1->print(o);
	o << "]";
}

bool GreaterThan::evaluate() {
	if (_A1->evaluate() > _A2->evaluate()) {return true;}
	else {return false;}
}

LessThan::LessThan(ArithmeticExpression *ae1, ArithmeticExpression *ae2) {
	this->A1 = ae1;
	this->A2 = ae2;
}

LessThan::~LessThan() {
	delete A1; 
	delete A2;
}

void LessThan::print(std::ostream & o) const {
	o << "[";
	A1->print(o);
	o << " < ";
	A2->print(o);
	o << "]";
}


bool LessThan::evaluate() {
	if (A1->evaluate() < A2->evaluate()) {return true;}
	else {return false;}
}