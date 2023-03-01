run: main
	./main

main: main.o token.o scanner.o statemachine.o symbol.o node.o parser.o
	g++ -o main main.o token.o scanner.o statemachine.o symbol.o node.o parser.o

main.o: main.cpp
	gcc -c main.cpp

token.o: token.cpp
	gcc -c token.cpp

scanner.o: scanner.cpp
	gcc -c scanner.cpp

statemachine.o: statemachine.cpp
	gcc -c statemachine.cpp

symbol.o: symbol.cpp
	gcc -c symbol.cpp

node.o: node.cpp
	gcc -c node.cpp

parser.o: parser.cpp
	gcc -c parser.cpp