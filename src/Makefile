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
$(BDX_OBJECT_OBJ): \
	$(UTIL_H) \
	$(BDX_OBJECT_H) \
	$(BDX_OBJECT_CXX)
	$(CXX) $(CXXOPT) -c $(BDX_OBJECT_CXX) -o $(BDX_OBJECT_OBJ)
$(PARTICLE_OBJ): \
	$(UTIL_H) \
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
$(HANDLER_OBJ): \
	$(UTIL_H) \
	$(PARTICLE_H) \
	$(HANDLER_CXX)
	$(CXX) $(CXXOPT) -c $(HANDLER_CXX) -o $(HANDLER_OBJ)
$(MAIN_OBJ): \
	$(BDX_H) \
	$(UTIL_H) \
	$(BDX_OBJECT_H) \
	$(PARTICLE_H) \
	$(HARD_SPHERE_H) \
	$(UTIL_OBJ) \
	$(BDX_OBJECT_OBJ) \
	$(PARTICLE_OBJ) \
	$(HARD_SPHERE_OBJ) \
	$(HANDLER_OBJ) \
	$(MAIN_CXX)
	$(CXX) $(CXXOPT) -c $(MAIN_CXX) -o $(MAIN_OBJ)
$(BDX): $(MAIN_OBJ)
	$(CXX) $(CXXOPT) \
		$(UTIL_OBJ) \
		$(BDX_OBJECT_OBJ) \
		$(PARTICLE_OBJ) \
		$(HARD_SPHERE_OBJ) \
		$(HANDLER_OBJ) \
		$(MAIN_OBJ) \
		-o \
		$(BDX) \
		$(LIBS)
clean:
	rm -f ../obj/*.o
	rm -f $(BDX)
