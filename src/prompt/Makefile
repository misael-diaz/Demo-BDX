#!/usr/bin/make
#
# BDX						December 05, 2023
#
# source: src/prompt/Makefile
# author: @misael-diaz
#
# Synopsis:
# Defines the Makefile for building the program with GNU make.
#
# Copyright (c) 2023 Misael Díaz-Maldonado
# Copyright (c) 2024 UCF-Research Group
# This file is released under the GNU General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#

include make-inc

all: $(PROMPT_OBJ)

$(PROMPT_OBJ): $(HEADERS) $(PROMPT_CXX)
	$(CXX) $(INC) $(CXXOPT) -c $(PROMPT_CXX) -o $(PROMPT_OBJ)

clean:
	/bin/rm -f *.obj
