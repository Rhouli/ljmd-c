#*********************************
# -*- Makefile -*-
# Author: Ryan Houlihan
# Email: ryan.houlihan90@gmail.com
#*********************************

SHELL = /bin/sh
GCC = g++

# ALl tests to be produced
TESTS =	test_pair_LJ
TESTS_SRC = $(TESTS:%=%.cpp)
MYMD_DIR = ../..
MYMD_SRC_DIR = 	$(MYMD_DIR)/SRC
MYMD_INC_DIR = 	$(MYMD_DIR)/INC
USER_DIR = ..
LINKFLAGS =	-o
INC_DIR = INC

INCLUDE = -I$(INC_DIR) -I$(MYMD_INC_DIR) -I$(GTEST)

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
###*********ARCHIVE INFO*********###
####################################

AR = ar
ARFLAGS = rcsv 
MD_OBJ = $(MYMD_DIR)/Obj-serial.x

####################################
###*********COMPILATION**********###
####################################

default: ${TESTS}

cleanAll:
	rm -rf ${TESTS} gtest.a gtest_main.a *.o 

.depend: $(TESTS_SRC)
	$(GCC) -MM $(INCLUDE) $^ > $@

# Create Object File
%.o: %.cpp
	$(GCC) ${GCCFLAGS} -o $@ -c $<

libmymd.a: $(MD_OBJ)
	$(AR) $(ARFLAGS) $@ $^

# Compile program
%: %.o $(GTEST)/gtest_main.a  $(GTEST)/gtest.a libmymd.a
	$(GCC) -o $@ ${LINKFLAGS} $^ 

sinclude .depend