# BDX Demo
This is the open-source version of the Brownian Dynamics code BDX that I developed for the
University of Puerto Rico - Mayagüez UPRM. The demo is a minimalistic version and has
been implemented in an entirely different way. The BDX code leverages AVX512 instructions
for performance in HPC CPUs while this demo does not even try to perform such
optimizations.

The purpose of this demo is to showcase my ability to write C/C++ code, it's not
intended for research work because this code does not even commit the simulation data to
disk and also it does not perform data processing while the simulation is executing.
If you wish to perform Brownian dynamics simulations I encourage you to explore
open-source projects such as [LAMMPS](https://github.com/lammps/lammps).

Hopefully the demo can be understood as is without comments all over the place even for
developers who are not familiar with Brownian dynamics simulations.

## Rationale for not using the STL

We do not intend to rely on the STL because there's no real need for developing this
application.
We know how many entities we will simulate beforehand and that number will not change
throughout the simulation. We are also able to optimize the application (via domain
partitioning) with a simple user-defined data structure backed by C-style arrays
so that we don't see the need to introduce the `std::vector`. If we ever need more complex
data structures we shall seriously consider leveraging the STL to develop this
application.

And last but not least, this is a demo meant to showcase my ability
to solve problems with just core language features. Just going to add here that the
creator of C++, Bjarne Stroupstrup, knows that developers are free to use his programming
language as they see fit, he has also said that mastering C++ is not about using the
latest features but to know when and how to use them. He also admits it is not possible to
implement the most performant features of the STL without (carefully) using all the core
features of C++ (
source: Lex Fridman's [podcast](https://www.youtube.com/watch?v=uTxRF5ag27A)
). This is enough reason for me to be on the path of mastering the use of C-style
pointers; only then I shall be able to appreciate the facilities of the STL such as
smart pointers.

## Influence of open-source game engines

I have spent a considerable amount of time studying Quake's source code because I would
like to create some games on my spare time. I have learned that I need to know a lot
more such as graphics programming in order to understand Quake's source code but
found out about how they did memory management and thought that would be useful for
some of my projects like this one.

Thus, I borrowed from there (which is fine because it's GPL'd source code like this one)
and made some modifications to implement a simple garbage collector GC. The GC makes it
possible to abort execution of the simulation if we encounter an error without incurring
on memory leaks. This is also the reason why I did not implement destructors since the GC
will handle that at the end of the simulation.

## BDX Simulation Video

Sample Video of a BDX Simulation (click on the image below to watch on youtube):
[![Watch the video](https://img.youtube.com/vi/BrQCCio_Z5c/hqdefault.jpg)](https://youtu.be/BrQCCio_Z5c)

The video was generated with the actual BDX code (which is the proprietary and fully
featured version owned by the University of Puerto Rico - Mayagüez UPRM) not this demo.

I might add videos produced by this open-source version later.
