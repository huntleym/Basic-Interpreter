all: main

main: main.cpp Program.cpp ArithmeticExpression.cpp BooleanExpression.cpp Command.cpp
	g++ -g -Wall -std=c++11 main.cpp Command.cpp BooleanExpression.cpp \
	ArithmeticExpression.cpp Program.cpp -o main

.PHONY: clean
clean:
	rm main