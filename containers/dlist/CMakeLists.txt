# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(dlist VERSION 1.0.0 DESCRIPTION "Doubly linked list container" LANGUAGES C)

# add source to library
add_library(dlist SHARED src/dlist.c)

# Declare public API of lib
set_target_properties(dlist PROPERTIES PUBLIC_HEADER inc/dlist.h)

# Include relative paths
target_include_directories(dlist PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:include>)
    
# Add linking libraries
target_link_libraries(dlist PUBLIC containers_common)

if(BUILD_TYPE STREQUAL "debug")
    target_link_libraries(dlist PRIVATE -fsanitize=address)
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
