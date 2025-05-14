#ifndef BDX_SYS_HPP
#define BDX_SYS_HPP

#include <cmath>
#include "bdx.hpp"

static_assert(BDX_NUM_CELLS_X == BDX_NUM_CELLS_Y);
static_assert(BDX_NUM_CELLS_X == BDX_NUM_CELLS_Z);
static_assert((BDX_NUM_CELLS_X * BDX_NUM_CELLS_Y * BDX_NUM_CELLS_Z) == BDX_NUM_PARTICLES);

constexpr long num_cell_x = BDX_NUM_CELLS_X;
constexpr long num_cell_y = BDX_NUM_CELLS_Y;
constexpr long num_cell_z = BDX_NUM_CELLS_Z;
constexpr long num_particles = BDX_NUM_PARTICLES;

constexpr double Pi = M_PI;
constexpr double num_cell_x_f64 = num_cell_x;
constexpr double num_cell_y_f64 = num_cell_y;
constexpr double num_cell_z_f64 = num_cell_z;
constexpr double volume_fraction = BDX_VOLUME_FRACTION;
constexpr double cell_length = cbrt( (4.0 * Pi / 3.0) / volume_fraction );
constexpr double cell_width = cell_length;
constexpr double cell_height = cell_length;
constexpr double box_length = (num_cell_x_f64 * cell_length);
constexpr double box_width  = (num_cell_y_f64 * cell_width);
constexpr double box_height = (num_cell_z_f64 * cell_height);
constexpr double cell_center = (0.5 * cell_length);
constexpr double cell_length_inv = (1.0 / cell_length);
constexpr double cc = cell_center;
constexpr double cl = cell_length;
constexpr double bl = box_length;
constexpr double bw = box_width;
constexpr double bh = box_height;
constexpr double hl = (0.5 * box_length);
constexpr double cl_inv = cell_length_inv;

#endif
