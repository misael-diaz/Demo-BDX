#!/usr/bin/make
#
# BDX						December 05, 2023
#
# source: src/virtual/Makefile
# author: @misael-diaz
#
# Synopsis:
# Defines the Makefile for building the program with GNU make.
#
# Copyright (c) 2023 Misael Diaz-Maldonado
# Copyright (c) 2024 UCF-Research Group
# This file is released under the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#

include make-inc

all: $(VIRTUAL_OBJ)

$(VIRTUAL_OBJ): $(HEADERS) $(VIRTUAL_CXX)
	$(CXX) $(INC) $(CXXOPT) -c $(VIRTUAL_CXX) -o $(VIRTUAL_OBJ)

clean:
	/bin/rm -f *.obj
