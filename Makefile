run: clean main
	./main

main: main.o Token.o Scanner.o StateMachine.o Symbol.o Node.o Parser.o
	g++ -o main main.o Token.o Scanner.o StateMachine.o Symbol.o Node.o Parser.o

main.o: main.cpp
	gcc -c main.cpp

clean:
	rm -f *.o main

token.o: Token.cpp
	gcc -c Token.cpp

scanner.o: Scanner.cpp
	gcc -c Scanner.cpp

statemachine.o: StateMachine.cpp
	gcc -c StateMachine.cpp

symbol.o: Symbol.cpp
	gcc -c Symbol.cpp

node.o: Node.cpp
	gcc -c Node.cpp

parser.o: Parser.cpp
	gcc -c Parser.cpp