#include "util.h"
#include "Timer.h"
#include "BDX.h"

Timer::Timer ()
{
	return;
}

Timer::Timer (ssize_t const walltime) : _walltime_(walltime)
{
	return;
}

void Timer::bind (BDX *app)
{
	this->app = app;
}

void *Timer::operator new (size_t size)
{
	return util::malloc(size);
}

void Timer::operator delete (void *p)
{
	p = util::free(p);
}

void Timer::begin ()
{
	this->_begin_ = ((ssize_t) time(NULL));
}

void Timer::end ()
{
	this->_end_ = ((ssize_t) time(NULL));
}

void Timer::etime ()
{
	ssize_t const walltime = this->_walltime_;
	ssize_t const elapsedTime = (this->_end_ - this->_begin_);
	ssize_t const etime = elapsedTime;
	if (etime >= walltime) {
		this->app->_exec_ = false;
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
source: src/timer/Timer.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
