#*********************************
# -*- Makefile -*-
# Author: Ryan Houlihan
# Email: ryan.houlihan90@gmail.com
#*********************************

SHELL=/bin/sh

default: serial parallel

serial parallel:
	$(MAKE) MFLAGS=$(MFLAGS) -C Obj-$@

test:	serial parallel
	$(MAKE) MFLAGS=$(MFLAGS) -C LIB/MD_Test

clean:
	$(MAKE) MFLAGS=$(MFLAGS) -C Obj-serial clean
	$(MAKE) MFLAGS=$(MFLAGS) -C Obj-parallel clean
	$(MAKE) MFLAGS=$(MFLAGS) -C LIB/MD_Test
