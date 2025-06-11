# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(libc59_common VERSION 1.0.0 DESCRIPTION "libc59 common")

set(CMAKE_SHARED_LIBRARY_PREFIX "")

# add source to library
add_library(libc59_common SHARED src/libc59_common.c)

# Declare public API of lib
set_target_properties(libc59_common PROPERTIES PUBLIC_HEADER inc/libc59_common.h)

# Include relative paths
target_include_directories(libc59_common PRIVATE inc)
target_include_directories(libc59_common PRIVATE src)

add_subdirectory(test)

# Compile options
add_compile_options(-std=c11 -g -Wall -Wextra -Wshadow -Wunused -Wconversion -pedantic  -fdiagnostics-color=always -fsanitize=address)

# Output to bin directory
set_target_properties(libc59_common PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ../bin 
    LIBRARY_OUTPUT_DIRECTORY ../bin
    RUNTIME_OUTPUT_DIRECTORY ../bin     
)

# Install rules
include(GNUInstallDirs)
install(TARGETS libc59_common
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Enable testing
include(CTest)

# Add test suite with valgrind -> # -s = show suppressed errors
add_test(NAME test_common_59_interface
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    ../bin/test_common_59_interface
)
set_tests_properties(test_common_59_interface
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_common_59_edge_cases
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    ../bin/test_common_59_edge_cases
)
set_tests_properties(test_common_59_edge_cases
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

#-----------------------------------------------------------------------------------------------------------------------
# CLI CMake commands -> cmake .. -> cmake --build . -> sudo cmake install (this last one works?)
#-----------------------------------------------------------------------------------------------------------------------
