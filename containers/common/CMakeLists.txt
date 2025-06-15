# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(container_common_59 VERSION 1.0.0 DESCRIPTION "Common items for libc59 containers")

# add source to library
add_library(container_common_59 SHARED src/container_common_59.c)

# Declare public API of lib
set_target_properties(container_common_59 PROPERTIES PUBLIC_HEADER inc/container_common_59.h)

# Include relative paths
target_include_directories(container_common_59 PRIVATE inc)
target_include_directories(container_common_59 PRIVATE src)
target_include_directories(container_common_59 PRIVATE ../../common/src)
target_include_directories(container_common_59 PRIVATE ../../common/inc)

add_subdirectory(test)

# Compile options
if(BUILD_TYPE STREQUAL "debug")
    add_compile_options(-std=c11 -g -Wall -Wextra -Wshadow -Wunused -Wconversion -pedantic  -fdiagnostics-color=always -fsanitize=address)
elseif(BUILD_TYPE STREQUAL "release")
    add_compile_options(-std=c11 -O2 -fPIC -D_FORTIFY_SOURCE=2 -Wl,-z,relro -Wl,-z,now 
    -Wall -Wextra -Wshadow -Wunused -Wconversion -pedantic  -fdiagnostics-color=always)
else()
    message(FATAL_ERROR "Invalid build type, use -DBUILD_TYPE and set 'release' or 'debug'")
endif()

# Output to bin directory
set_target_properties(container_common_59 PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ../bin 
    LIBRARY_OUTPUT_DIRECTORY ../bin
    RUNTIME_OUTPUT_DIRECTORY ../bin     
)

# Install rules
include(GNUInstallDirs)
install(TARGETS container_common_59
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Enable testing
include(CTest)

# Add test suite with valgrind -> # -s = show suppressed errors
add_test(NAME test_container_common_59_interface
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    ../bin/test_container_common_59_interface
)
set_tests_properties(test_container_common_59_interface
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_container_common_59_edge_cases
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    ../bin/test_container_common_59_edge_cases
)
set_tests_properties(test_container_common_59_edge_cases
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

#-----------------------------------------------------------------------------------------------------------------------
# CLI CMake commands -> cmake .. -> cmake --build . -> sudo cmake install (this last one works?)
#-----------------------------------------------------------------------------------------------------------------------
