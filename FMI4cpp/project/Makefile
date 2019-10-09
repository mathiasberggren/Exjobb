# /usr/local/lib = Standard place for libraries, always searched by compiler so no need to include
# /usr/include/  = Standard place for include files, always searched by compiler so no need to include
_LDIR =/usr/local/lib == Standard place for libraries, no need to include
_IDIR =/usr/include/
LIBS=-lfmi4cpp -ldl -lstdc++fs -lzip -lpython2.7
IDIR=$(_IDIR:%=-I%)
LDIR=$(_LDIR:%=-L%)
#IDIR_OPTIONAL = $(addprefix -I,$(_IDIR))
#LDIR_OPTIONAL = $(addprefix -L,$(_LDIR))

CC=g++
CCFLAGS=-std=c++17 -Wall -Weffc++ -Wextra -pedantic
HEADERS = PID.h net.h
OBJ = simulate_pendulum.o PID.o net.o

%.o: %.cc $(HEADERS)
	$(CC) -c -o $@ $< $(CCFLAGS)

simulate_pendulum: $(OBJ)
	$(CC) $^ -o $@ $(LIBS) $(CCFLAGS)

#pid.o:	PID.cc
#	$(CC) -c $^ -o $@

#net.o:	net.cc
#	$(CC) -c $^ -o $@ 

#simulate_pendulum.o: simulate_pendulum.cc
#	$(CC) -c $^ -o $@ 

.PHONY:	clean

clean:
	rm -f ./*.o ./simulate_pendulum
