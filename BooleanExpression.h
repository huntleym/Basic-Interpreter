#include <iostream>
//#include "ArithmeticExpression.h"

class ArithmeticExpression;
// This file is for classes that have to do with Boolean expressions

class BooleanExpression {
  	// abstract class for a Boolean expression

 	public:
 		virtual ~BooleanExpression() {};
  		virtual void print (std::ostream & o) const = 0;
  		// pure virtual print function. Don't implement!
  		virtual bool evaluate() = 0;
};

// add below child classes that inherit from BooleanExpression

class Equals : public BooleanExpression {
	public:
		Equals(ArithmeticExpression *ae1, ArithmeticExpression *ae2);
		~Equals();

		virtual void print(std::ostream & o) const;

		virtual bool evaluate(); //virtual for ~polymorphism~

	private:
		ArithmeticExpression *_a1, *_a2;

};

class GreaterThan : public BooleanExpression {
	public:
		GreaterThan(ArithmeticExpression *ae1, ArithmeticExpression *ae2);
		~GreaterThan();

		virtual void print(std::ostream & o) const;

		virtual bool evaluate();

	private:
		ArithmeticExpression *_A1, *_A2;
};

class LessThan : public BooleanExpression {
	public:
		LessThan(ArithmeticExpression *ae1, ArithmeticExpression *ae2);
		~LessThan();
		virtual void print(std::ostream & o) const;

		virtual bool evaluate();

	private:
		ArithmeticExpression *A1, *A2;
};