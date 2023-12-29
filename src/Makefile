#!/usr/bin/make
#
# BDX				December 05, 2023
#
# source: src/Makefile
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

all: tests

utils:
	@$(MAKE) -C util
ids: utils
	@$(MAKE) -C id
kinds: utils
	@$(MAKE) -C kind
vectors: utils
	@$(MAKE) -C vector
objects: utils vectors
	@$(MAKE) -C object
particles: utils ids kinds vectors objects
	@$(MAKE) -C particle
spheres: utils ids kinds vectors objects particles
	@$(MAKE) -C sphere
systems: utils ids kinds vectors objects particles spheres
	@$(MAKE) -C box
tests: utils ids kinds vectors objects particles spheres systems
	@$(MAKE) -C test

clean:
	@$(MAKE) -C util clean
	@$(MAKE) -C id clean
	@$(MAKE) -C kind clean
	@$(MAKE) -C vector clean
	@$(MAKE) -C object clean
	@$(MAKE) -C particle clean
	@$(MAKE) -C sphere clean
	@$(MAKE) -C box clean
	@$(MAKE) -C test clean
