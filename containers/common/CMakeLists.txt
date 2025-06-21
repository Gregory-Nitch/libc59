# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(container_common_59 VERSION 1.0.0 DESCRIPTION "Common items for libc59 containers" LANGUAGES C)

# add source to library
add_library(container_common_59 SHARED src/container_common_59.c)

# Declare public API of lib
set_target_properties(container_common_59 PROPERTIES PUBLIC_HEADER inc/container_common_59.h)

# Includes
target_include_directories(container_common_59 PUBLIC inc)

# Library Links
target_link_libraries(container_common_59 PUBLIC c59_common)

if(BUILD_TYPE STREQUAL "debug")
    target_link_libraries(container_common_59 PRIVATE -fsanitize=address)
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
install(TARGETS container_common_59
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
