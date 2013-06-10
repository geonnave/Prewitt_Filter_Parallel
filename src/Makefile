FILE = main
EXEC_PATH = bin
IMG_PATH = images

all: clean compile run

compile:
	g++ -o $(EXEC_PATH)/$(FILE) $(FILE).cpp prewitt.cpp -lpthread -lX11 -fopenmp
run:
	$(EXEC_PATH)/$(FILE) $(IMG_PATH)/$(IMG)
clean:
	rm -f $(EXEC_PATH)/$(FILE)
