SHELL = /bin/sh

CC =		g++
CCFLAGS =	-O
# ALl tests to be produced
TESTS= 		test_pair_LJ
LAMMPS = 	../../../src
USER_DIR = ..
LINKFLAGS =	-o
LIB =           -llmp_serial
# Link to library and Stubs
STUBS = 	../../../src/STUBS
MPI = 		${STUBS}/libmpi.a


# GOOGLE TEST
#----------------------------------------------------------------------
# Google Test root dir
GTEST_DIR = ../gtest

# Google Test preprocessor flags
GTEST = $(GTEST_DIR)/include

# Google test C++ compiler flags
CXXFLAGS = -g -Wall -Wextra

# All Google Test Headers
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
		$(GTEST_DIR)/include/gtest/internal/*.h

all: ${TESTS}

test_pair_LJ: test_pair_LJ.o

cleanAll:
	rm -rf ${TESTS} gtest.a gtest_main.a *.o 

# Builds a test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

EXTRA_LIBS = -I${GTEST} -I${STUBS} -I${LAMMPS}

# Create Object File

%.o: %.cpp %.h ${GTEST_HEADERS}
	$(CC) ${EXTRA_LIBS} ${CCFLAGS} ${EXTRA_INC} -o $@ -c $<

# Compile program

%: %.o GTest/gtest_main.a  GTest/gtest.a
	$(CC) -L${LAMMPS} $^ ${LIB} ${MPI_LIB} -lpthread ${LINKFLAGS} $@
