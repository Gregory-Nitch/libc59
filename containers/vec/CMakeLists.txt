# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(vec_59 VERSION 1.0.0 DESCRIPTION "Vector container")

# add source to library
add_library(vec_59 SHARED src/vec_59.c)

# Declare public API of lib
set_target_properties(vec_59 PROPERTIES PUBLIC_HEADER inc/vec_59.h)

# Add other library to link in
target_link_libraries(vec_59 PUBLIC ${PROJECT_SOURCE_DIR}/../../common/bin/libc59_common.so)

# Include relative paths
target_include_directories(vec_59 PRIVATE inc)
target_include_directories(vec_59 PRIVATE src)
target_include_directories(vec_59 PRIVATE ../common/src)
target_include_directories(vec_59 PRIVATE ../common/inc)
target_include_directories(vec_59 PRIVATE ../../common/src)
target_include_directories(vec_59 PRIVATE ../../common/inc)

add_subdirectory(test)

# Compile options
add_compile_options(-std=c11 -Wall -Wextra -Wshadow -Wunused -fdiagnostics-color=always)

# Output to bin directory
set_target_properties(vec_59 PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ../bin 
    LIBRARY_OUTPUT_DIRECTORY ../bin
    RUNTIME_OUTPUT_DIRECTORY ../bin     
)

# Install rules
include(GNUInstallDirs)
install(TARGETS vec_59
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Enable testing
include(CTest)

# Add test suite with valgrind -> # -s = show suppressed errors
add_test(NAME test_vec_59_interface
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    ../bin/test_vec_59_interface
)
set_tests_properties(test_vec_59_interface
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_vec_59_edge_cases
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    ../bin/test_vec_59_edge_cases
)
set_tests_properties(test_vec_59_edge_cases
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

#-----------------------------------------------------------------------------------------------------------------------
# CLI CMake commands -> cmake .. -> cmake --build . -> sudo cmake install (this last one works?)
#-----------------------------------------------------------------------------------------------------------------------
