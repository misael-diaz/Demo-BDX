#!/usr/bin/env python3
# -*- coding: utf-8 -*-
'''
BDX                                             July 20, 2023

source: plot-msd.py
author: @misael-diaz

Synopsis:
Plots the time evolution of the Mean Squared Displacement MSD.

Copyright (c) 2023 Misael Díaz-Maldonado
Copyright (c) 2024 UCF-Research Group
This file is released under the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

References:
[0] R Johansson, Numerical Python: Scientific Computing and Data
    Science Applications with NumPy, SciPy, and Matplotlib, 2nd edition.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.
'''

from numpy import loadtxt
import matplotlib as mpl
from matplotlib import pyplot as plt

plt.close('all')
plt.ion()
fig, ax = plt.subplots()
t, msd, amsd = loadtxt("msd.txt").transpose()
ax.loglog(t, 2 * t, linestyle="--", color="black", label="theory")
ax.loglog(t, msd, linestyle="-", color="red", label="bds")
ax.set_title("Translational Time-Averaged MSD")
ax.set_xlabel("time")
ax.set_ylabel("MSD")
ax.legend()

fig, ax = plt.subplots()
ax.loglog(t, 1.5 * t, linestyle="--", color="black", label="theory")
ax.loglog(t, amsd, linestyle="-", color="red", label="bds")
ax.set_title("Rotational Time-Averaged MSD")
ax.set_xlabel("time")
ax.set_ylabel("MSD")
ax.legend()
