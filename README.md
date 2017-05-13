[![Build Status](https://travis-ci.org/r4nd0m6uy/charguychess.svg?branch=master)](https://travis-ci.org/r4nd0m6uy/charguychess)

The software for the DIY chess hardware we want to build with my father.

# Prerequists
This software depends on the following libraries:

* libevent >= 2.0
* libconfig++ >= 1.5

The test application depends on the following library:

* cpputest >= 3.8

# Compilation
> mkdir build ; cd build

> cmake ..

> make

## Compiling the tests
Install Cpputest >= 3.8 or set the CPPUTEST_HOME environment variable manually:

> export CPPUTEST_HOME=/opt/cpputest

Then add *COMPILE_TESTS=ON* argument to cmake

> mkdir build ; cd build

> cmake ../ -DCOMPILE_TESTS=ON 

> make

# Run
Once the application was compiled succesfully, run:

> ./src/cgc

# Hardware
The hardware is being built and more information will come ...

# Simulation hardware
Run:

> ./src/cgc -H sim

A file in */tmp/board_input* will be created where you can write bitboards values. Some games
are available in *tests/simulation*, for example:

> cat ../tests/simulation/e2e4 > /tmp/board_input

# Missing features
To do so it is playable:
* stalemate
* draw

Nice feature for the future:
* Read from PGN
* FEN notation

# TODO
To do list so I know where I was when a dig into the project again:
* Add states for computer turn using UCI engine
* Add output driver to show computer moves / hints on the board
