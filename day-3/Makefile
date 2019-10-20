all: solution run
.PHONY : all

run: solution
	./solution
.PHONY : run

clean:
	rm -f solution solution.o
.PHONY : clean

solution: solution.d
	dmd -unittest -main solution.d
