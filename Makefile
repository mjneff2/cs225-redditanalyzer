
main : main.o
	clang++ main.o -o main

main.o : main.cpp
	clang++ -c main.cpp

clean : 
	rm *.o main
