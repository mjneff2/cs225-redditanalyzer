
main : main.o data.o graph.o
	clang++ main.o data.o graph.o -o main

test: test.o graph.o catchmain.o
	clang++ test.o graph.o catchmain.o -o test

test.o: test.cpp catch/catch.hpp
	clang++ -c test.cpp

catchmain.o : catch/catchmain.cpp catch/catch.hpp
	clang++ -c catch/catchmain.cpp

main.o : main.cpp
	clang++ -c main.cpp

data.o: data.cpp
	clang++ -c data.cpp

graph.o: graph.cpp
	clang++ -c graph.cpp

clean : 
	rm *.o main
