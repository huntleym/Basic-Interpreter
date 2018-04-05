#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>

class Program;
class ArithmeticExpression;
class BooleanExpression;

class Command {
  // abstract class for a BASIC Command

 public:
 	virtual ~Command() {};
    virtual void print (std::ostream & o) const = 0;
  // pure virtual print function. Don't implement!

    //pure virtual execute() function
    virtual void execute () = 0;
};

// add below child classes that inherit from Command

class Print : public Command {
 //prints value of AEXPR -- we have to evaluate it!
public:
	Print(ArithmeticExpression *ae);
	~Print();
	virtual void print(std::ostream & o) const;

	void fullprint();
	//calls evaluate on _ae

	virtual void execute(); //returns line number

private:
	ArithmeticExpression *_ae;

};

class LetVar : public Command { //make just one let 
public:
	LetVar(Variable *var, ArithmeticExpression *ae);
	~LetVar();

	virtual void print(std::ostream & o) const;

	//calls evaluate on _ae
	//if ae evaluates to something, store it inside var
	//by calling initialize() on _var; overwrites prev value in _var

	virtual void execute();

private:
	ArithmeticExpression *_ae;
	Variable *_var; //Variable or variable array
};

class LetVarArray : public Command {
public:
	LetVarArray(VarArray *ae, ArithmeticExpression *var);
	~LetVarArray();

	virtual void print(std::ostream & o) const;

	//evaluate _ae and stores the value into var array at pos found
	//be evaluating the ae inside VarA

	virtual void execute();

private:
	VarArray *varA; //VarArray
	ArithmeticExpression *_ae;
}; 

class GoTo : public Command { //UNFINISHED-WHAT TO DO WITH LINE OBJECT
public:
	GoTo(int l);
	~GoTo();

	virtual void print(std::ostream & o) const;

	int getLine() const;

	//Line* jumpto(Line* linej);
	//jumps to line j and forgets where it came from
	//class Program that stores a vector of line objects
	//if no line linej, throw exception "Line not found" and terminate

	//in the Program::runProgram() function, we are going to change 
	virtual void execute();

private:
	int line;

};

class IfThen : public Command {
public:
	IfThen(BooleanExpression *be, int l);
	~IfThen();
	virtual void print(std::ostream & o) const;

	int getLine() const;

	//evaluates the boolean expression
	//if true, jump to line -- do this manually in main?

	virtual void execute();

private:
	BooleanExpression *_be;
	int _linej;

};

class GoSub : public Command {
public:
	GoSub(int lgo, int lfrom);
	~GoSub();
	virtual void print(std::ostream & o) const;
	//Line* camefrom(); //returns the line that initiated the last GoSub

	//jumps to line and "remembers where it came from" by calling AddGoSub on Program
	virtual void execute();

private:
	int linej; //this is line it is going to
	int linefrom;

};

class Return : public Command {
public:
	Return();
	~Return();

	virtual void print(std::ostream & o) const;
	//Line* return(GoSub *g); //returns the line object that return puts us at

	//goes to GoSub at top of stack in Program and deletes from that stack
	//then it calls GoTo on the line after that
	virtual void execute();

private:
	//Line _line;

};

class End : public Command {
public:
	End();
	~End();
	virtual void print(std::ostream & o) const;

	virtual void execute();

};

#endif