RUNDIR = bin
FILE = main

all: clean compile run

compile:
	g++ -o $(RUNDIR)/$(FILE) $(FILE).cpp -lpthread -lX11
run:
	$(RUNDIR)/$(FILE)
clean:
	rm -f $(RUNDIR)/$(FILE)
