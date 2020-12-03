
main : main.o data.o
	clang++ main.o data.o graph.o -o main

main.o : main.cpp
	clang++ -c main.cpp

data.o: data.cpp
	clang++ -c data.cpp

graph.o: graph.cpp
	clang++ -c graph.cpp

clean : 
	rm *.o main
