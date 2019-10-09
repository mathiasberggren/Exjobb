CC=g++
CCFLAGS=-Wall -Weffc++ -Wextra -Wpedantic -lwiringPi -lpthread
HEADERS = ./include/*.h
OBJ = ./main.o ./include/*.cc ./include/*.cpp

default: simulation

%.o: %.cc $(HEADERS)
	$(CC) -c -o $@ $< $(CCFLAGS) 

simulation: $(OBJ)
	$(CC) -o $@ $^ $(CCFLAGS)

.PHONY: clean

clean:
	rm -f ./*.o ./include/*.o ./*.swp ./include/*.swp
