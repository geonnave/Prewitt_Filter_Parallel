FILE = main
EXEC_PATH = bin
IMG_PATH = images

all: clean compile run

compile:
	g++ -o $(EXEC_PATH)/$(FILE) $(FILE).cpp prewitt.cpp -lpthread -lX11 -fopenmp -O3 -march=native
run:
	$(EXEC_PATH)/$(FILE) $(IMG_PATH)/$(IMG) $(THREADS)
clean:
	rm -f $(EXEC_PATH)/$(FILE)

run_test:
	$(EXEC_PATH)/$(FILE) 