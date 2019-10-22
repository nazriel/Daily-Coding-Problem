all: run
.PHONY : all

run: solution
	./solution
.PHONY : run

clean:
	rm -f ./solution.o ./solution
.PHONY : clean

solution: solution.o
	gcc -o solution solution.o

solution.o: solution.c
	gcc -Wall -Wextra -pedantic -std=c11 -c -o solution.o solution.c
