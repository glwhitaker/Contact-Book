OPTIONS = -g
PROGRAM = main

all: $(PROGRAM)

run: $(PROGRAM)
	./main

$(PROGRAM): main.cpp contact.cpp
	g++ $(OPTIONS) main.cpp contact.cpp -o main -lncurses

clean:
	@rm -f main
