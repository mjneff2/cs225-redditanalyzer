
main : main.o data.o graph.o
	clang++ main.o data.o graph.o -o main

test: test.o graph.o
	clang++ test.o graph.o -o test

test.o: test.cpp
	clang++ -c test.cpp

main.o : main.cpp
	clang++ -c main.cpp

data.o: data.cpp
	clang++ -c data.cpp

graph.o: graph.cpp
	clang++ -c graph.cpp

clean : 
	rm *.o main
