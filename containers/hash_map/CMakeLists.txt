# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(hash_map_59 VERSION 1.0.0 DESCRIPTION "Hash map container" LANGUAGES C)

# add source to library
add_library(hash_map_59 SHARED src/hash_map_59.c)

# Declare public API of lib
set_target_properties(hash_map_59 PROPERTIES PUBLIC_HEADER inc/hash_map_59.h)

# Include relative paths
target_include_directories(hash_map_59 PUBLIC inc)

# Add libraries to link too
target_link_libraries(hash_map_59 PUBLIC m llist_59 container_common_59) # m = <math.h>

if(BUILD_TYPE STREQUAL "debug")
    target_link_libraries(hash_map_59 PRIVATE -fsanitize=address)
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
install(TARGETS hash_map_59
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Enable testing
include(CTest)

# Add test suite with valgrind -> # -s = show suppressed errors
add_test(NAME test_hash_map_59_interface
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_hash_map_59_interface>
)
set_tests_properties(test_hash_map_59_interface
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_hash_map_59_edge_cases
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_hash_map_59_edge_cases>
)
set_tests_properties(test_hash_map_59_edge_cases
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)
