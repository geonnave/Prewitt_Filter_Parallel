RUNDIR = bin
FILE = main

all: clean compile run

compile:
	# g++ -o $(RUNDIR)/$(FILE) $(FILE).cpp -lopencv_core -lopencv_flann -lopencv_imgproc -lopencv_highgui -lopencv_ml
	g++ -ggdb `pkg-config --cflags opencv` -o `basename main.cpp .cpp` main.cpp `pkg-config --libs opencv`
run:
	$(RUNDIR)/$(FILE)
clean:
	rm -f $(RUNDIR)/$(FILE)

