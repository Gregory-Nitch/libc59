# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(c59_common VERSION 1.0.0 DESCRIPTION "libc59 common" LANGUAGES C)

# add source to library
add_library(c59_common SHARED src/c59_common.c)

# Declare public API of lib
set_target_properties(c59_common PROPERTIES PUBLIC_HEADER inc/c59_common.h)

# Include relative paths
target_include_directories(c59_common PUBLIC inc)

# Add Linking libraries
if(BUILD_TYPE STREQUAL "debug")
    target_link_libraries(c59_common PRIVATE -fsanitize=address)
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
install(TARGETS c59_common
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
