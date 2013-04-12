all: clean compile run

compile:
	gcc -o main main.c -fopenmp
run:
	./main
clean:
	rm -f main
