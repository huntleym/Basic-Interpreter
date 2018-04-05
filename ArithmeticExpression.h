#ifndef ARITHMETICEXPRESSION_H
#define ARITHMETICEXPRESSION_H

#include <iostream>
#include <stack>
#include <vector>
#include <map>

class ArithmeticExpression;

//this Error class handles all of the possible errors:
	//Division by zero
	//Line does not exist
		//GoTo
		//IfThen
		//GoSub
	//No previous GoSub -- if GoSub stack empty

class Error {
public:
	//what different things do we have to do for diff errors?

	//division by zero constructor
	Error(int line, std::string message, ArithmeticExpression* ae1, 
		ArithmeticExpression* ae2); 

	//no lines for GoTo, IfThen, GoSub contructor 
	Error(std::string s, int line, int linej);

	//no previous GoSub constructor
	Error(std::string s, int line); //also take in line number

	//for END
	Error(std::string s);

	~Error();

	void what();

private:
	//Variable* v; //stores the string object
	ArithmeticExpression* ae1;
	ArithmeticExpression* ae2;
	int lineat;
	int linenot;
	std::string message; //this tells us what it is

};

// This file is for classes that have to do with arithmetic expressions

class ArithmeticExpression {
  // abstract class for an arithmetic expression

 	public:
 		virtual ~ArithmeticExpression() {};
  		virtual void print (std::ostream & o) const = 0; //std::ostream &o
  		// pure virtual print function. Don't implement!
  		virtual int evaluate() = 0;

  		virtual std::string getName() = 0;

};

/* if you prefer to have an abstract "BinaryArithmeticExpression"
   class or something like that, feel free to insert it and
   have Addition inherit from that instead. HELL NAW SUCK A DICK*/

class Constant : public ArithmeticExpression {
public:
	Constant(int x);
	~Constant();

	virtual void print(std::ostream & o) const;

	virtual int evaluate();

	virtual std::string getName();
 
private:
	int value;
};

class Variable : public ArithmeticExpression {
public:
	Variable(std::string s);
	~Variable();

	virtual void print(std::ostream & o) const;

	virtual int evaluate();

	//void initialize(int x);
	void initialize(std::map<std::string, int>* allvars);

	virtual std::string getName();

private:
	std::string name;
	int value; //signed
	std::map<std::string, int>* allvars = NULL;

};


class VarArray : public ArithmeticExpression {
public:
	friend class Command;
	VarArray(std::string s, ArithmeticExpression *ae);
	~VarArray();

	virtual void print(std::ostream & o) const;

	virtual int evaluate();

	//adds a value to a certain position
	void addValue(int pos, int value);

	virtual std::string getName();

	ArithmeticExpression* getInner();

private:
	std::string name;
    ArithmeticExpression *inner;
	std::map<int, int> vararray; //doesn't need to be a pointer
	//size equal to the range of a signed integer
	//but we imagine them to have "infinite" size
	//so there can never be segfaults

};

class Addition : public ArithmeticExpression {
	public:
		Addition (ArithmeticExpression *ae1, ArithmeticExpression *ae2);
		~Addition ();
  
  		virtual void print (std::ostream & o) const;
  		// because the class is not abstract, we must implement print

  		//function to evaluate the expression
  		virtual int evaluate();

  		virtual std::string getName();
  
 	private:
  		ArithmeticExpression *_ae1, *_ae2; // the left and right term
};

// add below other classes that are needed

class Subtraction : public ArithmeticExpression {
	public:
		Subtraction(ArithmeticExpression *ae1, ArithmeticExpression *ae2);
		~Subtraction();

		virtual void print (std::ostream & o) const;

		virtual int evaluate();

		virtual std::string getName();

	private:
		ArithmeticExpression *ae1, *ae2;
};

class Multiplication : public ArithmeticExpression {
	public:
		Multiplication(ArithmeticExpression *ae1, ArithmeticExpression *ae2);
		~Multiplication();

		virtual void print (std::ostream & o) const;

		virtual int evaluate();

		virtual std::string getName();

	private:
		ArithmeticExpression *Ae1, *Ae2;
};

class Division : public ArithmeticExpression {
	public:
		Division(ArithmeticExpression *ae1, ArithmeticExpression *ae2);
		~Division();

		virtual void print (std::ostream & o) const;

		virtual int evaluate();

		virtual std::string getName();

	private:
		ArithmeticExpression *_Ae1, *_Ae2;

};


#endif