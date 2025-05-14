# BDX demo
This is the open-source version of the Brownian Dynamics code BDX that I developed for the
University of Puerto Rico - Mayagüez UPRM. The demo is a minimalistic version and has
been implemented in an entirely different way. The BDX code leverages AVX512 instructions
for performance in HPC CPUs while this demo does not even try to perform such
optimizations.

The demo can be understood as is without comments all over the place.

We do not intend to rely on the STL because there's no real need to develop this
application.
We know how many entities we will simulate beforehand and that number will not change
throughout the simulation. We are also able to optimize the application (via domain
partitioning) with a simple user-defined data structure backed by C-style arrays
that we don't see the need to introduce the `std::vector`. If we ever need more complex
data structures we shall seriously consider leveraging the STL to develop this
application. And last but not least, this is a demo meant to showcase my ability
to solve problems with core language features.

We have borrowed from GPL'd id Software code.

Sample Video of a BDX Simulation (click on the image below to watch on youtube):
[![Watch the video](https://img.youtube.com/vi/BrQCCio_Z5c/hqdefault.jpg)](https://youtu.be/BrQCCio_Z5c)

The video was generated with the actual BDX code (which is the proprietary and fully
featured version owned by the University of Puerto Rico - Mayagüez UPRM) not this demo.

I might add videos produced by this open-source version later.
