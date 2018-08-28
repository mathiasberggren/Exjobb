CC=g++
CCFLAGS=-Wall -Weffc++ -Wextra -Wpedantic
HEADERS = ./include/*.h
OBJ = ./main.o ./include/*.cc

default: simulation

%.o: %.cc $(HEADERS)
	$(CC) -c -o $@ $< $(CCFLAGS)

simulation: $(OBJ)
	$(CC) -o $@ $^ $(CCFLAGS)

.PHONY: clean

clean:
	rm -f ./*.o ./include/*.o
