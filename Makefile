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

# Constants 
START_ANGLE ?=3.14
# 0 = PID, 1 = NN, 2 = Linear, 3 = Tree
CONTROLLER_MODE ?=0
# 0 = Off, 1 = On
TRAINING_MODE ?=0
FILENAME ?="test_file"
DIRECTORY ?="."

DEFINED_CONSTS=-DTRAINING_MODE=$(TRAINING_MODE) -DCONTROLLER_MODE=$(CONTROLLER_MODE) -DFILENAME=$(FILENAME) -DDIRECTORY=$(DIRECTORY) -DSTART_ANGLE=$(START_ANGLE)
SUFFIX=-$(START_ANGLE)-$(CONTROLLER_MODE)-$(TRAINING_MODE)

_ML_H=linear_model.h r_tree.h net.h
_ML_O=linear_model.o r_tree.o net.o

ML_DIR=./ML-models/
ML_H=$(_ML_H:%=$(ML_DIR)%)
ML_O=$(_ML_O:%=$(ML_DIR)%)

CC=g++
CCFLAGS=-std=c++17 -g -Wall -Wextra -pedantic # Removed because of warnings from matplotlib -Weffc++  
HEADERS:=PID.h $(ML_H) 
OBJ:=simulate_pendulum.o PID.o $(ML_O)

ifeq ($(TRAINING_MODE),1)
	OUT:=train_model-$(CONTROLLER_MODE)
else
	OUT:=simulate_pendulum$(SUFFIX)
endif

all: $(OUT)

%.o: %.cc $(HEADERS)
	$(CC) -c -o $@ $< $(IDIR) $(LDIR) $(CCFLAGS) $(DEFINED_CONSTS)

$(OUT): $(OBJ) 
	$(CC) $^ -o $@ $(IDIR) $(LDIR) $(LIBS) $(CCFLAGS) 

.PHONY:	clean

clean:
	rm -f ./*.o ./simulate_pendulum-* $(ML_DIR)*.o ./train_model*
