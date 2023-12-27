#!/usr/bin/make
#
# BDX						December 05, 2023
#
# source: src/object/Makefile
# author: @misael-diaz
#
# Synopsis:
# Defines the Makefile for building the program with GNU make.
#
# Copyright (c) 2023 Misael Diaz-Maldonado
# This file is released under the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#

include make-inc

all: $(OBJECT_OBJ)

$(OBJECT_OBJ): $(HEADERS) $(OBJECT_CXX)
	$(CXX) $(INC) $(CXXOPT) -c $(OBJECT_CXX) -o $(OBJECT_OBJ)

clean:
	/bin/rm -f *.obj
