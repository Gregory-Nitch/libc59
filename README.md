# libc59
C Library of useful C modules

# Requirements / Tools
- CMake version 3.22.1 or greater
- Built with gcc version 13.3.0 on Ubuntu 24.04

*There is no installation support for other OS types in the current CMake install rules*

# Building, Testing, Installing w/ CMAKE CLI
- Make build directory -> **From Repo Root Dir** $ mkdir bld
- Change to bld directory -> $ cd bld
- Configure CMake -> $ cmake -DBUILD_TYPE=<debug||release>  .. 
- Build -> $ cmake --build . [-jX]
- Run tests -> $ ctest [-jX]
- Install -> $ sudo cmake install (Not tested)

*-jX is optional; X is number of cores to use during test or building ie, -j8 or -j16*
