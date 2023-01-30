main: main.o token.o
	g++ -o main main.o token.o

main.o: main.cpp
	gcc -c main.cpp

token.o: token.cpp
	gcc -c token.cpp