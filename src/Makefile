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
vectors: utils
	@$(MAKE) -C vector
objects: utils vectors
	@$(MAKE) -C object
particles: utils ids vectors objects
	@$(MAKE) -C particle
systems: utils ids vectors objects particles
	@$(MAKE) -C box
tests: utils ids vectors objects particles systems
	@$(MAKE) -C test

clean:
	@$(MAKE) -C util clean
	@$(MAKE) -C id clean
	@$(MAKE) -C vector clean
	@$(MAKE) -C object clean
	@$(MAKE) -C particle clean
	@$(MAKE) -C box clean
	@$(MAKE) -C test clean
