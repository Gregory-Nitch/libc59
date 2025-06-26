# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(containers_common VERSION 1.0.0 DESCRIPTION "Common items for libc59 containers" LANGUAGES C)

# add source to library
add_library(containers_common SHARED src/containers_common.c)

# Declare public API of lib
set_target_properties(containers_common PROPERTIES PUBLIC_HEADER containers/common/inc/containers_common.h)

# Includes
target_include_directories(containers_common PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:include>)

# Library Links
target_link_libraries(containers_common PUBLIC common)

if(BUILD_TYPE STREQUAL "debug")
    target_link_libraries(containers_common PRIVATE -fsanitize=address)
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
