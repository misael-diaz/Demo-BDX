#!/usr/bin/make
#
# BDX						December 05, 2023
#
# source: src/janus/Makefile
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

all: $(JANUS_OBJ)

$(JANUS_OBJ): $(HEADERS) $(JANUS_CXX)
	$(CXX) $(INC) $(CXXOPT) -c $(JANUS_CXX) -o $(JANUS_OBJ)

clean:
	/bin/rm -f *.obj
