# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(hash_map VERSION 1.0.0 DESCRIPTION "Hash map container" LANGUAGES C)

# add source to library
add_library(hash_map SHARED src/hash_map.c)

# Declare public API of lib
set_target_properties(hash_map PROPERTIES PUBLIC_HEADER inc/hash_map.h)

# Include relative paths
target_include_directories(hash_map PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:include>)
    
# Add libraries to link too
target_link_libraries(hash_map PUBLIC m llist containers_common) # m = <math.h>

if(BUILD_TYPE STREQUAL "debug")
    target_link_libraries(hash_map PRIVATE -fsanitize=address)
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
