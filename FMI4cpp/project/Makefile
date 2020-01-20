# /usr/local/lib = Standard place for libraries, always searched by compiler so no need to include
# /usr/include/  = Standard place for include files, always searched by compiler so no need to include
_LDIR =/usr/local/lib 
# /home/lapbottom/Programming/Exjobb/Shark/build/lib/ 
_IDIR =/usr/include/ ./ML-models/ 
# /home/lapbottom/Programming/Exjobb/Shark/include/ /home/lapbottom/Programming/Exjobb/Shark/build/include/
LIBS=-lfmi4cpp -ldl -lstdc++fs -lzip -lpython2.7 -lboost_serialization -lgomp
# lshark
IDIR=$(_IDIR:%=-I%)
LDIR=$(_LDIR:%=-L%)
#IDIR_OPTIONAL = $(addprefix -I,$(_IDIR))
#LDIR_OPTIONAL = $(addprefix -L,$(_LDIR))

ML_DIR=./ML-models/
_ML_H=linear_model.h r_tree.h net.h
_ML_O=linear_model.o r_tree.o net.o

ML_H=$(_ML_H:%=$(ML_DIR)%)
ML_O=$(_ML_O:%=$(ML_DIR)%)

CC=g++
CCFLAGS=-std=c++17 -Wall -Weffc++ -Wextra -pedantic
HEADERS = PID.h $(ML_H) 
OBJ = simulate_pendulum.o PID.o $(ML_O)

%.o: %.cc $(HEADERS)
	$(CC) -c -o $@ $< $(IDIR) $(LDIR) $(CCFLAGS)

simulate_pendulum: $(OBJ) 
	$(CC) $^ -o $@ $(IDIR) $(LDIR) $(LIBS) $(CCFLAGS)

.PHONY:	clean

clean:
	rm -f ./*.o ./simulate_pendulum $(ML_DIR)*.o
