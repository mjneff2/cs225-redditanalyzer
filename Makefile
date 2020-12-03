
main : main.o data.o
	clang++ main.o data.o -o main

main.o : main.cpp
	clang++ -c main.cpp

data.o: data.cpp
	clang++ -c data.cpp

clean : 
	rm *.o main
