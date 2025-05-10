#!/usr/bin/make
#
# BDX				December 05, 2023
#
# source: Makefile
# author: @misael-diaz
#
# Synopsis:
# Defines the Makefile for building the program with GNU make.
#
# Copyright (c) 2023 Misael Diaz-Maldonado
#
# This file is released under the GNU General Public License version 3 only
# as published by the Free Software Foundation.
#

include make-inc

mode=run

ifeq ($(mode),run)
	CXXOPT=$(CXXRUN)
else
	CXXOPT=$(CXXDEV)
endif

LIBS=-lm

export CXX
export CXXOPT
export LIBS

all: BDX

BDX:
	@mkdir -p obj && mkdir -p bin
	@$(MAKE) -C src
clean:
	@$(MAKE) -C src clean
