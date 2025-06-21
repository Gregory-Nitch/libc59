# libc59
C Library of useful C modules

# Building, Testing, Installing w/ CMAKE CLI
- Make build directory -> **From Repo Root Dir** $ mkdir bld
- Change to bld directory -> $ cd bld
- Configure CMake -> $ cmake -DBUILD_TYPE=<debug||release>  .. 
- Build -> $ cmake --build .
- Run tests -> $ ctest 
- Install -> $ sudo cmake install (this last one works?)
