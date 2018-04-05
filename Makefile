all: hw5

hw5: hw5.cpp Program.cpp ArithmeticExpression.cpp BooleanExpression.cpp Command.cpp
	g++ -g -Wall -std=c++11 hw5.cpp Command.cpp BooleanExpression.cpp \
	ArithmeticExpression.cpp Program.cpp -o hw5

.PHONY: clean
clean:
	rm hw5