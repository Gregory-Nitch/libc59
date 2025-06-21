# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(libc59 VERSION 1.0.0 DESCRIPTION "libc59 libraries" LANGUAGES C)


# Compile options
if(BUILD_TYPE STREQUAL "debug")
    add_compile_options(-std=c11 -g -Wall -Wextra -Wshadow -Wunused -Wconversion -pedantic  -fdiagnostics-color=always -fsanitize=address)
elseif(BUILD_TYPE STREQUAL "release")
    add_compile_options(-std=c11 -O2 -fPIC -D_FORTIFY_SOURCE=2 -Wl,-z,relro -Wl,-z,now 
    -Wall -Wextra -Wshadow -Wunused -Wconversion -pedantic  -fdiagnostics-color=always)
else()
    message(FATAL_ERROR "Invalid build type, use -DBUILD_TYPE and set 'release' or 'debug'")
endif()

# Set a global build directory for all sub-projects
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add subdirectories for each library
add_subdirectory(common)
add_subdirectory(containers/common)
add_subdirectory(containers/dlist)
add_subdirectory(containers/llist)
add_subdirectory(containers/vec)
add_subdirectory(containers/hash_map)

include(GNUInstallDirs)

# Enable testing for the top-level project
enable_testing()

# If you want to run all tests from the top level, you can use a custom target
# This assumes your sub-projects register their tests with CTest
add_custom_target(run_all_tests COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                  COMMENT "Running all tests. . .")

# To make 'make test' at the top level run all tests
add_test(NAME AllSubprojectTests COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
