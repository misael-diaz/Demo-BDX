#include "util.h"
#include "Driver.h"
#include "Looper.h"
#include "Logger.h"
#include "Timer.h"
#include "BDX.h"

Looper::Looper ()
{
	return;
}

void Looper::bind (BDX *app)
{
	this->app = app;
}

void *Looper::operator new (size_t size)
{
	return util::malloc(size);
}

void Looper::operator delete (void *p)
{
	p = util::free(p);
}

size_t Looper::step () const
{
	return this->_step_;
}

size_t Looper::num_steps () const
{
	return this->_num_steps_;
}

void Looper::loop ()
{
	Logger *logger = this->app->logger;
	Driver *driver = this->app->driver;
	this->app->timer->begin();
	this->_step_ = 0;
	logger->txt();
	while (this->app->exec() && this->step() != this->num_steps()) {
		size_t istep = 0;
		constexpr size_t isteps = (GLOBAL_TIME_STEP_LOGGER / GLOBAL_TIME_STEP);
		while (istep != isteps) {
			driver->BrownianMotion();
			driver->contain();
			++istep;
		}
		logger->txt();
		this->app->timer->end();
		this->app->timer->etime();
		this->_step_ += isteps;
	}

	if (this->step() == this->num_steps()) {
		logger->txt();
	}
}

/*

BDX                                             December 31, 2023

Copyright (C) 2023 Misael Díaz-Maldonado
Copyright (C) 2024 UCF-Research Group

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

author: @misael-diaz
source: src/looper/Looper.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
