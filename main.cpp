#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <stack>
#include "Program.h"
#include "ArithmeticExpression.h"
#include "BooleanExpression.h"
#include "Command.h"

using namespace std;

//parser function: returns AE* - takes in a string

ArithmeticExpression* parser(string &s) {

	//if string at i is a letter
    //if string at i is an arithmetic operator
    //if string at i is a digit (constant, can be negative)
    //if string at i is a '[' or ']'
    //if string at i is a '(' or ')'

    stack<char> charstack;// = new stack<char>;
    stack<ArithmeticExpression*> aestack;// = new stack<ArithmeticExpression*>;

	for (unsigned int i=0; i<s.length(); i++) {
		if (s[i] == '(') { //WORKS

            //push to charstack
            charstack.push(s[i]);
		}
		else if (s[i] == ')') {

            //look at aestack
            ArithmeticExpression* rhs = aestack.top();
            aestack.pop();
            ArithmeticExpression* lhs = NULL;
            if (!aestack.empty()) {
                lhs = aestack.top();
                aestack.pop();
            }
            //else {return rhs;}
            
            if (!charstack.empty()) {
                //assume there is an arithmetic operator
                if (charstack.top() == '+') {
                    charstack.pop(); //popping operator
                    charstack.pop(); //popping open parentheses
                    //create Addition object and push to the stack
                    ArithmeticExpression* a = new Addition(lhs, rhs);
                    aestack.push(a);
                }
                else if (charstack.top() == '-') {
                    charstack.pop(); //popping operator
                    charstack.pop(); //popping open parentheses
                    //create Subtraction object and push to the stack
                    ArithmeticExpression* a = new Subtraction(lhs, rhs);
                    aestack.push(a);
                }
                else if (charstack.top() == '*') {
                    charstack.pop(); //popping operator
                    charstack.pop(); //popping open parentheses
                    //create Addition object and push to the stack
                    ArithmeticExpression* a = new Multiplication(lhs, rhs);
                    aestack.push(a);
                }
                else if (charstack.top() == '/') {
                    charstack.pop(); //popping operator
                    charstack.pop(); //popping open parentheses
                    //create Addition object and push to the stack
                    ArithmeticExpression* a = new Division(lhs, rhs);
                    aestack.push(a);
                }
            }
		}
		else if (isalpha(s[i])) {
			string var = "";
			while (isalpha(s[i])) {
				var += s[i];
				i++;
			}
            
			if (i < s.size() && s[i] == '[') {
                int open = 1, closed = 0;
				string inner = "";
                i++;
                while (open != closed) {
                    if (s[i] == '[') {
                        open++;
                    }
                    else if (s[i+1] == ']') {
                        closed++;
                    }
                    inner+= s[i];
                    i++;
                }

				// how to parse vararray within the function for parser
				ArithmeticExpression* inside = parser(inner);
				ArithmeticExpression* whole = new VarArray(var, inside);
				aestack.push(whole);
				i--;
			}
			else {
				ArithmeticExpression* va = new Variable(var);
				aestack.push(va);
				i--;
			}
			//cout << var << endl;
		}
		else if (s[i] == '-') {
            if (i == 0 || s[i-1] == '+' || s[i-1] == '-' || s[i-1] == '*' || s[i-1] == '/' || s[i-1] == '(') {
			//if (isdigit(s[i+1]) && (charstack->empty() || charstack->top() == '(')) {
				i++;
				string co = "-";
				while (isdigit(s[i])) {
					co += s[i];
					i++;
				}
				//create Constant object and put stoi(co)
				ArithmeticExpression* con = new Constant(stoi(co));
				aestack.push(con);
				i--;
			}
			else {//if it's just a subtraction operator instead of a negative sign
                charstack.push(s[i]);

			}
		}
		else if (isdigit(s[i])) {
			string co = "";
			while (isdigit(s[i])) {
				co += s[i];
				i++;
			}
			//create Constant object and put stoi(co)
			ArithmeticExpression* con = new Constant(stoi(co));
			aestack.push(con);
			i--;
		}
		else if (s[i] == '+') {
			charstack.push(s[i]);
		}
		else if (s[i] == '*') {
			charstack.push(s[i]);
		}
		else if (s[i] == '/') {
			charstack.push(s[i]);
		}
	}

    return aestack.top();

}


int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide an input file." << endl;
    return 1;
  }
  ifstream input(argv[1]);


  //initialize Program object
  Program program; 


  string curr; // the current line

  //loop to read all lines of the program, pretty print each,
  //then create a line object using that line and put it into 
  //the Program object
  while(getline(input, curr)) {
    stringstream ss;
    ss << curr;
    string command; // the command
    int line;  // the line number
    
    ss >> line;
    cout << line << " ";
    ss >> command;

    //here, we will be creating Variables, VariableArrays, and Lines
    //we have to make sure we don't create two of the same variable
    //or variable array

    //check that name is not key in map

    if (command == "PRINT") { //TO FINISH
      //prints the value of the arithmetic expression

    	string AEXPR = "";
    	while (!ss.fail()) {
    		string temp;
    		ss >> temp;
    		AEXPR += temp;
    	}

    	ArithmeticExpression* ae = parser(AEXPR); //PARSERRRRRRRRR

    	Command* pr = new Print(ae);
    	pr->print(cout);
    	cout << endl;

        //add 
        program.addLine(line, pr);

    	//delete Line and Command later

    }
    else if (command == "LET") { //TODO
    	//syntax: <VAR> <AEXPR>
    	//writes AEXPR into variable VAR
    	//syntax: <VAR> [<AEXPR1>] <AEXPR2>
    	//write AEXPR2 into array VAR at position AEXPR1

    	//first, we must read in the first variable/vararray
    	//then, we must read in the AEXPR

        /*1 LET X 1
        2 LET X Y
        3 LET X Y [20]*/



        string rest;
        getline(ss, rest);

        unsigned int j = 0;
        string var1 = "";

        //reads in first bit of white space before variable name
        while (rest[j] == ' ') { 
            j++;
        }
        //reads in variable name
        while (rest[j] != ' ') {
            var1 += rest[j];
            j++;
        }

        //now we are at whitespace -- we need to read through it again
        while(rest[j] == ' ') {
            j++;
        }

        string ae1temp = var1, ae2temp = "";
        //now we look through the variable we just read and check if it's a '['
        int i = 0;
        while (isalpha(var1[i])) {
            i++;
        }
        bool isArray = false;
        if (var1[i] == '[') {
            isArray = true;
        } 

        //now read in rest
        for (; j<rest.length(); j++) {
            ae2temp += rest[j];
        }

        //remove whitespace
        string AEXPR1 = "", AEXPR2 = "";

        for (unsigned int i = 0; i<ae1temp.length(); i++) {
            if (ae1temp[i] != ' ') {
                AEXPR1 += ae1temp[i];
            }
        }
        for (unsigned int i = 0; i<ae2temp.length(); i++) {
            if (ae2temp[i] != ' ') {
                AEXPR2 += ae2temp[i];
            }
        }
        
        //parse AEXPR1 and AEXPR2
        ArithmeticExpression* first = parser(AEXPR1);
        ArithmeticExpression* second = parser(AEXPR2);

        //create let object
        Command* let = NULL;
        if (isArray) {
            //std::cout << "In let function: " << std::endl;
            let = new LetVarArray((VarArray*)first, second);
        }
        else {
            let = new LetVar((Variable*)first, second);
        }
        let->print(cout);
        cout << endl;

        program.addLine(line, let);
    	
    }
    else if (command == "IF") { //TODO
    	//syntax: IF <BEXPR> THEN <LINEJ>
    	//if boolean expression BEXPR is true, jump to line LINEJ
    	string BEXPR = "";
    	string temp;
    	ss >> temp;
    	while (temp != "THEN") {
    		BEXPR += temp;
    		ss >> temp;
    	}

    	string AEXPR1 = "", AEXPR2 = "";
    	BooleanExpression* be = NULL;
    	char op;
    	//loop through BEXPR string until we reach '=', '<', or '>'
    	//so we can separate AEXPR1 string and AEXPR2 string
    	unsigned int i;
    	for (i=0; i < BEXPR.length(); i++) {
    		AEXPR1 += BEXPR[i]; 
    		if (BEXPR[i+1] == '=') {
    			op = '=';
    			break;
    		}
    		else if (BEXPR[i+1] == '<') {
    			op = '<';
    			break;
    		} 
    		else if (BEXPR[i+1] == '>') {
    			op = '>';
    			break;
    		}
    	}
    	for (i+=1; i<BEXPR.length(); i++) {
    		AEXPR2+= BEXPR[i];
    	}
    	//parse

    	ArithmeticExpression* ae1 = NULL;
    	ArithmeticExpression* ae2 = NULL;
    	//parse these
    	ae1 = parser(AEXPR1);
    	ae2 = parser(AEXPR2);
    	
    	if (op == '=') {
    		be = new Equals(ae1, ae2);
    	}
    	if (op == '>') {
    		be = new GreaterThan(ae1, ae2);
    	}
    	if (op == '<') {
    		be = new LessThan(ae1, ae2);
    	}
    	//after parsing
    	int linenumber;
    	ss >> linenumber;
    	//put into IfThen class
    	Command* c = new IfThen(be, linenumber);
    	c->print(cout);
    	cout << endl;

        //add 
        program.addLine(line, c);

        //delete Line and Command later

    }
    else if (command == "GOTO") {
    	//syntax: <LINEJ>
    	//jump to line LINEJ
    	int linenumber;
    	ss >> linenumber;
    	Command* g = new GoTo(linenumber);
    	g->print(cout);
    	cout << endl;
    	
        //add 
        program.addLine(line, g);

        //delete Line and Command later
    }
    else if (command == "GOSUB") {
    	//syntax: GOSUB <LINEJ>
    	//jump to line LINEJ and remember the line you came from
    	int linenumber;
    	ss >> linenumber;
    	Command* g = new GoSub(linenumber, line);
    	g->print(cout);
    	cout << endl;

    	//add line to Program
        program.addLine(line, g);

        //delete Line and Command later
    }
    else if (command == "RETURN") {
    	//go back to the line immediately after the line of the most recent GOSUB
    	Command* r = new Return();
    	r->print(cout);
    	cout << endl;

    	//add 
        program.addLine(line, r);

        //delete Line and Command later
    }
    else if (command == "END") {
    	Command* e = new End();
    	e->print(cout);
    	cout << endl;

    	//add 
        program.addLine(line, e);

        //delete Line and Command later
    }
    else {
      // This should never happen - print an error?
    	cout << "Error: command not valid." << endl;
    }
  }

  
    try {
        //put loops in try block -- then you can break out of them
        //execute command
        //iterate through allLines
        for (; program.itAllLines < program.allLines.size(); program.itAllLines++) {
            //call execute on each command
            //each element in allLines is a line struct
            program.allLines[program.itAllLines] -> c -> execute(); 

            //what to do for jumps?? suck a dick that's what
        }

        //program.runProgram();
    } catch (Error & e) { //division by zero
        e.what();

        //exceptions will automatically exit
    }

  return 0;
} 
