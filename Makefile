
main : main.o graph.o
	clang++ main.o graph.o -o main

test: test.o graph.o catchmain.o
	clang++ test.o graph.o catchmain.o -o test

test.o: tests/test.cpp catch/catch.hpp
	clang++ -c tests/test.cpp

catchmain.o : catch/catchmain.cpp catch/catch.hpp
	clang++ -c catch/catchmain.cpp

main.o : main.cpp
	clang++ -c main.cpp

graph.o: graph/graph.cpp
	clang++ -c graph/graph.cpp

clean : 
	rm *.o main
