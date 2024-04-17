#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
BDX                                             September 18, 2023

source: msd.py
author: @misael-diaz

Synopsis:
Computes time-averaged Mean Squared Displacements MSDs.

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
"""

from numpy import arange
from numpy import vstack
from numpy import newaxis
from numpy import loadtxt
from numpy import savetxt
from numpy import zeros

def params():
  params = {}
  fname = 'ppBDXParams.txt'
  with open(fname, 'r') as f:
    for line in f:
      key, value = line.split(':')
      param = float(value)
      params[key] = param

  return params

def msd():
  prms = params()
  time_start = prms['GLOBAL_TIME_START']
  time_end = prms['GLOBAL_TIME_END']
  time_step = prms['GLOBAL_TIME_STEP']
  time_step_logger = prms['GLOBAL_TIME_STEP_LOGGER']
  num_particles = int(prms['NUM_PARTICLES'])
  num_steps = int((time_end - time_start) / time_step)
  step_size_logger = int(time_step_logger / time_step)

  times = arange(0, num_steps + step_size_logger, step_size_logger) * time_step
  num_data_files = times.size

  step_size_start, step_size_end = (0, num_data_files)
  step_sizes = arange(step_size_start, step_size_end).astype(int)
  msd = zeros([num_data_files])
  amsd = zeros([num_data_files])

  shifts = zeros([num_particles])
  displacements = zeros([num_particles])
  mult = step_size_multiplier = step_size_logger
  # loop-invariant: so far we have obtained `step_size' elements of the MSD arrays
  for step_size in step_sizes:
    begin, end = [0, (num_data_files - step_size)]
    num_steps = (end - begin)
    displacements[:] = 0
    shifts[:] = 0
    # loop-invariant: so far we have considered `i' steps to obtain this MSD element
    for i in range(begin, end):
      step_idx = i * mult
      step_idx_next = (i + step_size) * mult

      data_file = f"particles-{step_idx:015d}.txt"
      data_file_next = f"particles-{step_idx_next:015d}.txt"
      data = loadtxt(data_file).transpose()
      data_next = loadtxt(data_file_next).transpose()

      x1, y1, z1, theta1_x, theta1_y, theta1_z = data[5:11, :]
      x2, y2, z2, theta2_x, theta2_y, theta2_z = data_next[5:11, :]

      displacements += ( (x2 - x1)**2 + (y2 - y1)**2 + (z2 - z1)**2 )
      shifts += ( (theta2_x - theta1_x)**2 +
                  (theta2_y - theta1_y)**2 +
                  (theta2_z - theta1_z)**2 )

    avg_shift = shifts.sum() / (3 * num_particles * num_steps)
    avg_displacement = displacements.sum() / (3 * num_particles * num_steps)
    msd[step_size] = avg_displacement
    amsd[step_size] = avg_shift

  times = times[newaxis, :]
  msd = msd[newaxis, :]
  amsd = amsd[newaxis, :]
  results = vstack([times, msd, amsd]).transpose()
  return results

res = msd()
savetxt("msd.txt", res)
