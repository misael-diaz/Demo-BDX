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

oss:
	@$(MAKE) -C os
stacks:
	@$(MAKE) -C stack
handlers: particles
	@$(MAKE) -C handler
lists: particles
	@$(MAKE) -C list
utils:
	@$(MAKE) -C util
lmps:
	@$(MAKE) -C lmp
PRNGs: utils
	@$(MAKE) -C random
prompts: utils
	@$(MAKE) -C prompt
ids: utils
	@$(MAKE) -C id
kinds: utils
	@$(MAKE) -C kind
vectors: utils
	@$(MAKE) -C vector
objects: utils vectors
	@$(MAKE) -C object
particles: stacks utils ids kinds vectors objects
	@$(MAKE) -C particle
spheres: utils ids kinds vectors objects particles
	@$(MAKE) -C sphere
janus: utils ids kinds vectors objects particles spheres
	@$(MAKE) -C janus
spheroids: utils ids kinds vectors objects particles
	@$(MAKE) -C spheroid
chirals: utils ids kinds vectors objects particles spheroids
	@$(MAKE) -C chiral
boxes: utils ids kinds vectors objects particles spheres janus spheroids chirals
	@$(MAKE) -C box
BD: utils
	@$(MAKE) -C Brownian
systems: utils boxes particles BD
	@$(MAKE) -C system
virtuals: systems oss utils prompts vectors particles
	@$(MAKE) -C virtual
configs: utils
	@$(MAKE) -C config
integrators: utils
	@$(MAKE) -C integrator
drivers: utils
	@$(MAKE) -C driver
loopers: utils
	@$(MAKE) -C looper
timers: utils
	@$(MAKE) -C timer
loggers: utils
	@$(MAKE) -C logger
BDX: boxes\
     handlers\
     PRNGs\
     lists\
     virtuals\
     configs\
     loopers\
     drivers\
     integrators\
     prompts\
     systems\
     loggers\
     timers\
     oss
	@$(MAKE) -C bdx
tests: lmps boxes handlers lists virtuals BDX
	@$(MAKE) -C test

clean:
	@$(MAKE) -C os clean
	@$(MAKE) -C util clean
	@$(MAKE) -C lmp clean
	@$(MAKE) -C random clean
	@$(MAKE) -C prompt clean
	@$(MAKE) -C stack clean
	@$(MAKE) -C handler clean
	@$(MAKE) -C list clean
	@$(MAKE) -C id clean
	@$(MAKE) -C kind clean
	@$(MAKE) -C vector clean
	@$(MAKE) -C object clean
	@$(MAKE) -C particle clean
	@$(MAKE) -C sphere clean
	@$(MAKE) -C janus clean
	@$(MAKE) -C spheroid clean
	@$(MAKE) -C chiral clean
	@$(MAKE) -C box clean
	@$(MAKE) -C Brownian clean
	@$(MAKE) -C system clean
	@$(MAKE) -C virtual clean
	@$(MAKE) -C config clean
	@$(MAKE) -C integrator clean
	@$(MAKE) -C driver clean
	@$(MAKE) -C looper clean
	@$(MAKE) -C timer clean
	@$(MAKE) -C logger clean
	@$(MAKE) -C bdx clean
	@$(MAKE) -C test clean
