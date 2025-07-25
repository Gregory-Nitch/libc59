# libc59
C Library of useful C modules

# Requirements / Tools
- CMake version 3.22.1 or greater
- Built with gcc version 13.3.0 on Ubuntu 24.04

*There is no installation support for other OS types in the current CMake install rules*

# Building, Testing, Installing w/ CMAKE CLI
- Make build directory -> **From Repo Root Dir** $ mkdir bld
- Change to bld directory -> $ cd bld
- Configure CMake -> $ cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DBUILD_TYPE=<release||debug> ..
- Build -> $ cmake --build . [-jX]
- Run tests -> $ ctest [-jX]
- Install -> $ sudo cmake --install .

*-jX is optional; X is number of cores to use during test or building ie, -j8 or -j16*

Then:
```C
#include "libc59/common.h"
#include "libc59/vec.h"
```
And in other projects CMakeLists.txt:
```CMake
list(APPEND CMAKE_PREFIX_PATH "/usr/local/lib/cmake/libc59")
find_package(libc59 REQUIRED)
target_link_libraries(mod-15-c PUBLIC libc59::common libc59::vec)
```

# Documentaion
- Run `doxygen ./Doxyfile`
- Output will go to ~/dox