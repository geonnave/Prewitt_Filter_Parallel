RUNDIR = bin
FILE = main

all: clean compile run

compile:
	gcc -o $(RUNDIR)/$(FILE) $(FILE).c
run:
	$(RUNDIR)/$(FILE)
clean:
	rm -f $(RUNDIR)/$(FILE)
