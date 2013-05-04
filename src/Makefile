FILE = main

all: clean compile run

compile:
	g++ -o $(FILE) $(FILE).cpp prewitt.cpp -lpthread -lX11
run:
	./$(FILE)
clean:
	rm -f $(FILE)
