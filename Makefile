main: main.o token.o scanner.o statemachine.o
	g++ -o main main.o token.o scanner.o statemachine.o

main.o: main.cpp
	gcc -c main.cpp

token.o: token.cpp
	gcc -c token.cpp

scanner.o: scanner.cpp
	gcc -c scanner.cpp

statemachine.o: statemachine.cpp
	gcc -c statemachine.cpp