#*********************************
# -*- Makefile -*-
# Author: Ryan Houlihan
# Email: ryan.houlihan90@gmail.com
#*********************************

SHELL=/bin/sh
GCC=g++
CFLAGS=-Wall -g -O3 -ffast-math -fomit-frame-pointer
LDLIBS=-lm

# list of source files
SRC_MAT= MyMD.cpp Helper.cpp Force.cpp Atom.cpp Integrator.cpp Pair.cpp Pair_LJ.cpp
INC_MAT= $(SRC:%.cpp=%.h)
OBJ=$(SRC:%.cpp=%.o)

SRCDIR=../SRC
INCDIR=../INC

vpath %.cpp $(SRCDIR)
vpath %.h $(INCDIR)

default: ../MyMD-serial.x

clean:
	rm -f *.mod *.o ../MyMD-serial.x

.depend: $(SRC_MAT)
	$(GCC) -MM -I $(INCDIR) $^ > $@

# linker rule
../MyMD-serial.x: $(OBJ)
	$(GCC) -o $@ $(CFLAGS) $^ $(LDLIBS)

# compilation pattern rule for objects
%.o: %.cpp
	$(GCC) -c $(CFLAGS) $< -I $(INCDIR)

sinclude .depend
