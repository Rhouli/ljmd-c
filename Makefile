#*********************************
# -*- Makefile -*-
# Author: Ryan Houlihan
# Email: ryan.houlihan90@gmail.com
#*********************************

SHELL=/bin/sh

default: serial parallel

serial parallel:
	$(MAKE) MFLAGS=$(MFLAGS) -C Obj-$@

clean:
	$(MAKE) MFLAGS=$(MFLAGS) -C Obj-serial clean
	$(MAKE) MFLAGS=$(MFLAGS) -C Obj-parallel clean

