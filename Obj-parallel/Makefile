#*********************************
# -*- Makefile -*-
# Author: Ryan Houlihan
# Email: ryan.houlihan90@gmail.com
#*********************************
SHELL=/bin/sh
GCC=g++
CFLAGS=-fopenmp -Wall -g -O3 -ffast-math -fomit-frame-pointer
LDLIBS=-lm

# list of source files
SRC_MAT= MyMD.cpp Helper.cpp Force.cpp Atom.cpp Integrator.cpp Pair.cpp Pair_LJ.cpp
INC_MAT = $(SRC:%.cpp=%.h)
OBJ=$(SRC:%.c=%.o)

SRCDIR=../src
INCDIR=../Include

vpath %.cpp $(SRCDIR)
vpath %.h $(INCDIR)

default: ../MyMD-parallel.x

clean:
	rm -f *.mod *.o ../MyMD-parallel.x

.depend: $(SRC_MAT)
	$(GCC) -MM -I $(INCDIR) $^ > $@

# linker rule
../MyMD-parallel.x: $(OBJ)
	$(GCC) -o $@ $(CFLAGS) $^ $(LDLIBS)

# compilation pattern rule for objects
%.o: $(SRC) $(INC)
	$(GCC) -c $(CFLAGS) $<

sinclude .depend