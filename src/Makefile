FILE = main
EXEC_PATH = bin
IMG_PATH = images

all: clean compile run

compile:
	g++ -o $(EXEC_PATH)/$(FILE) $(FILE).cpp prewitt.cpp -lpthread -lX11 -fopenmp -O2 -march=native
run:
	$(EXEC_PATH)/$(FILE) $(IMG_PATH)/$(IMG) $(THREADS) $(TEST)
clean:
	rm -f $(EXEC_PATH)/$(FILE)

run_test:
	$(EXEC_PATH)/$(FILE) $(IMG_PATH)/$(IMG) $(THREADS) $(TEST) > test_$(IMG)

compile_o2:
	g++ -o $(EXEC_PATH)/$(FILE)_O2 $(FILE).cpp prewitt.cpp -lpthread -lX11 -fopenmp -O2 -march=native

compile_o3:
	g++ -o $(EXEC_PATH)/$(FILE)_O3 $(FILE).cpp prewitt.cpp -lpthread -lX11 -fopenmp -O3 -march=native -ftree-vectorizer-verbose=5

run_param:
	$(EXEC_PATH)/$(FILE)_$(SUFIX) $(IMG_PATH)/$(IMG) $(THREADS)