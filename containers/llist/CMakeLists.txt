# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(llist_59 VERSION 1.0.0 DESCRIPTION "Linked list container")

# add source to library
add_library(llist_59 SHARED src/llist_59.c)

# Declare public API of lib
set_target_properties(llist_59 PROPERTIES PUBLIC_HEADER inc/llist_59.h)

# Include relative paths
target_include_directories(llist_59 PRIVATE inc)
target_include_directories(llist_59 PRIVATE src)
target_include_directories(llist_59 PRIVATE ../common/src)
target_include_directories(llist_59 PRIVATE ../common/inc)
target_include_directories(llist_59 PRIVATE ../../common/src)
target_include_directories(llist_59 PRIVATE ../../common/inc)


# Compile options
add_compile_options(-std=c11 -Wall -Wextra -Wshadow -Wunused -fdiagnostics-color=always)

# Install rules
include(GNUInstallDirs)
install(TARGETS llist_59
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#-----------------------------------------------------------------------------------------------------------------------
# CLI CMake commands -> cmake .. -> cmake --build . -> sudo cmake install (this last one work?)
#-----------------------------------------------------------------------------------------------------------------------


# TODO!!!!! update git ignore for bld and bin directories!!!!