A DIY chess hardware

# Compilation
> mkdir build ; cd build

> cmake ..

> make

## Compiling the tests
Install Cpputest>=3.8 or set the CPPUTEST_HOME environment variable:

> export CPPUTEST_HOME /opt/cpputest

Then add *COMPILE_TESTS=ON* argument to cmake

> mkdir build ; cd build

> cmake ../ -DCOMPILE_TESTS=ON 

> make

# Run the application
Once the application was compiled succesfully, run:

> ./src/cgc
