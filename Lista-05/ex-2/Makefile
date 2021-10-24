
output: main.o automata.o lexer.o
	g++ main.o automata.o lexer.o -o l5e2

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

automata.o: automata.cpp automata.h
	g++ -c automata.cpp

lexer.o: lexer.cpp lexer.h
	g++ -c lexer.cpp
