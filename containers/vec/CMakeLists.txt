# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(vec_59 VERSION 1.0.0 DESCRIPTION "Vector container" LANGUAGES C)

# add source to library
add_library(vec_59 SHARED src/vec_59.c)

# Declare public API of lib
set_target_properties(vec_59 PROPERTIES PUBLIC_HEADER inc/vec_59.h)

# Include relative paths
target_include_directories(vec_59 PUBLIC inc)

# Add Linking libraries
target_link_libraries(vec_59 PUBLIC container_common_59)

if(BUILD_TYPE STREQUAL "debug")
    target_link_libraries(vec_59 PRIVATE -fsanitize=address)
endif()

add_subdirectory(test)

# Compile options
if(BUILD_TYPE STREQUAL "debug")
    add_compile_options(-std=c11 -g -Wall -Wextra -Wshadow -Wunused -Wconversion -pedantic  -fdiagnostics-color=always -fsanitize=address -llibasan)
elseif(BUILD_TYPE STREQUAL "release")
    add_compile_options(-std=c11 -O2 -fPIC -D_FORTIFY_SOURCE=2 -Wl,-z,relro -Wl,-z,now 
    -Wall -Wextra -Wshadow -Wunused -Wconversion -pedantic  -fdiagnostics-color=always)
else()
    message(FATAL_ERROR "Invalid build type, use -DBUILD_TYPE and set 'release' or 'debug'")
endif()

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
    $<TARGET_FILE:test_vec_59_interface>
)
set_tests_properties(test_vec_59_interface
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_vec_59_edge_cases
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_vec_59_edge_cases>
)
set_tests_properties(test_vec_59_edge_cases
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)
