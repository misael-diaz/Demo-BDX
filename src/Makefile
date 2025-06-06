#!/usr/bin/make
#
# BDX                           December 05, 2023
#
# source: src/Makefile
# author: @misael-diaz
#
# Synopsis:
# Defines the Makefile for building the program with GNU make.
#
# Copyright (C) 2023 Misael Diaz-Maldonado
#
# This file is released under the GNU General Public License version 2 only
# as published by the Free Software Foundation.
#

include make-inc

all: $(BDX)

$(UTIL_OBJ): $(UTIL_CXX)
	$(CXX) $(CXXOPT) -c $(UTIL_CXX) -o $(UTIL_OBJ)
$(RANDOM_OBJ): \
	$(UTIL_H) \
	$(RANDOM_H) \
	$(RANDOM_CXX)
	$(CXX) $(CXXOPT) -c $(RANDOM_CXX) -o $(RANDOM_OBJ)
$(BIN_OBJ): \
	$(UTIL_H) \
	$(BIN_H) \
	$(BIN_CXX)
	$(CXX) $(CXXOPT) -c $(BIN_CXX) -o $(BIN_OBJ)
$(BDX_OBJECT_OBJ): \
	$(UTIL_H) \
	$(BDX_OBJECT_H) \
	$(BDX_OBJECT_CXX)
	$(CXX) $(CXXOPT) -c $(BDX_OBJECT_CXX) -o $(BDX_OBJECT_OBJ)
$(BOX_OBJ): \
	$(UTIL_H) \
	$(BOX_H) \
	$(BDX_OBJECT_H) \
	$(BOX_CXX)
	$(CXX) $(CXXOPT) -c $(BOX_CXX) -o $(BOX_OBJ)
$(PARTICLE_OBJ): \
	$(UTIL_H) \
	$(RANDOM_H) \
	$(BDX_OBJECT_H) \
	$(PARTICLE_H) \
	$(PARTICLE_CXX)
	$(CXX) $(CXXOPT) -c $(PARTICLE_CXX) -o $(PARTICLE_OBJ)
$(HARD_SPHERE_OBJ): \
	$(UTIL_H) \
	$(BDX_OBJECT_H) \
	$(PARTICLE_H) \
	$(HARD_SPHERE_H) \
	$(HARD_SPHERE_CXX)
	$(CXX) $(CXXOPT) -c $(HARD_SPHERE_CXX) -o $(HARD_SPHERE_OBJ)
$(LENNARD_JONES_SPHERE_OBJ): \
	$(UTIL_H) \
	$(BDX_OBJECT_H) \
	$(PARTICLE_H) \
	$(HARD_SPHERE_H) \
	$(LENNARD_JONES_SPHERE_H) \
	$(LENNARD_JONES_SPHERE_CXX)
	$(CXX) $(CXXOPT) -c $(LENNARD_JONES_SPHERE_CXX) -o $(LENNARD_JONES_SPHERE_OBJ)
$(MORSE_SPHERE_OBJ): \
	$(UTIL_H) \
	$(BDX_OBJECT_H) \
	$(PARTICLE_H) \
	$(HARD_SPHERE_H) \
	$(LENNARD_JONES_SPHERE_H) \
	$(MORSE_SPHERE_H) \
	$(MORSE_SPHERE_CXX)
	$(CXX) $(CXXOPT) -c $(MORSE_SPHERE_CXX) -o $(MORSE_SPHERE_OBJ)
$(SYSTEM_OBJ): \
	$(UTIL_H) \
	$(BOX_H) \
	$(BIN_H) \
	$(PARTICLE_H) \
	$(SYSTEM_H) \
	$(SYSTEM_CXX)
	$(CXX) $(CXXOPT) -c $(SYSTEM_CXX) -o $(SYSTEM_OBJ)
$(HANDLER_OBJ): \
	$(UTIL_H) \
	$(BOX_H) \
	$(BIN_H) \
	$(RANDOM_H) \
	$(PARTICLE_H) \
	$(SYSTEM_H) \
	$(HANDLER_CXX)
	$(CXX) $(CXXOPT) -c $(HANDLER_CXX) -o $(HANDLER_OBJ)
$(MAIN_OBJ): \
	$(BDX_H) \
	$(SYS_H) \
	$(BOX_H) \
	$(BIN_H) \
	$(UTIL_H) \
	$(RANDOM_H) \
	$(BDX_OBJECT_H) \
	$(PARTICLE_H) \
	$(HARD_SPHERE_H) \
	$(LENNARD_JONES_SPHERE_H) \
	$(MORSE_SPHERE_H) \
	$(HANDLER_H) \
	$(SYSTEM_H) \
	$(UTIL_OBJ) \
	$(RANDOM_OBJ) \
	$(BOX_OBJ) \
	$(BIN_OBJ) \
	$(BDX_OBJECT_OBJ) \
	$(PARTICLE_OBJ) \
	$(HARD_SPHERE_OBJ) \
	$(LENNARD_JONES_SPHERE_OBJ) \
	$(MORSE_SPHERE_OBJ) \
	$(HANDLER_OBJ) \
	$(SYSTEM_OBJ) \
	$(MAIN_CXX)
	$(CXX) $(CXXOPT) -c $(MAIN_CXX) -o $(MAIN_OBJ)
$(BDX): $(MAIN_OBJ)
	$(CXX) $(CXXOPT) \
		$(UTIL_OBJ) \
		$(RANDOM_OBJ) \
		$(BOX_OBJ) \
		$(BIN_OBJ) \
		$(BDX_OBJECT_OBJ) \
		$(PARTICLE_OBJ) \
		$(HARD_SPHERE_OBJ) \
		$(LENNARD_JONES_SPHERE_OBJ) \
		$(MORSE_SPHERE_OBJ) \
		$(HANDLER_OBJ) \
		$(SYSTEM_OBJ) \
		$(MAIN_OBJ) \
		-o \
		$(BDX) \
		$(LIBS)
clean:
	rm -f ../obj/*.o
	rm -f $(BDX)
