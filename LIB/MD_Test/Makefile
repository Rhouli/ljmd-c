#*********************************
# -*- Makefile -*-
# Author: Ryan Houlihan
# Email: ryan.houlihan90@gmail.com
#*********************************

SHELL = /bin/sh
GCC = g++

# ALl tests to be produced
TESTS =	test_pair_LJ
MYMD_SRC_DIR = 	../../src
MYMD_INC_DIR = 	../../Include
USER_DIR = ..
LINKFLAGS =	-o

INCLUDE = -I $(INC_DIR) -I $(MYMD_INC_DIR) -I $(GTEST_INC_DIR)
EXTRA_LIBS = -I${GTEST}

####################################
###*********GOOGLE TEST**********###
####################################

# Google Test root dir
GTEST_DIR = ../gtest

# Google Test preprocessor flags
GTEST = $(GTEST_DIR)/include

# Google test C++ compiler flags
GCCFLAGS = -g -Wall -Wextra -O

# All Google Test Headers
#GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
#		$(GTEST_DIR)/include/gtest/internal/*.h

GTEST_HEADERS_DIR = $(GTEST_DIR)/include/gtest		
		$(GTEST_DIR)/include/gtest/internal

####################################
###*********COMPILATION**********###
####################################

default: ${TESTS}

test_pair_LJ: test_pair_LJ.o

cleanAll:
	rm -rf ${TESTS} gtest.a gtest_main.a *.o 

.depend: $(SRC_MAT)
	$(GCC) -MM -I $(INCDOR) $^ > $@

# Create Object File
%.o: %.cpp
	$(GCC) ${GCCFLAGS} $(EXTRA_LIBS) -o $@ -c $< $(INCLUDE)

# Compile program
%: %.o GTest/gtest_main.a  GTest/gtest.a
	$(GCC) $^ -lpthread ${LINKFLAGS} $@

sinclude .depend