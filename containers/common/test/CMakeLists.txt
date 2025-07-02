# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(containers_common_test_suite VERSION 1.0.0 DESCRIPTION "Containers common unit tests" LANGUAGES C)

# Add test executables
add_executable(test_containers_common_interface src/test_containers_common_interface.c)
add_executable(test_containers_common_edge_cases src/test_containers_common_edge_cases.c)

# Add test relative paths
target_include_directories(test_containers_common_interface PRIVATE src)
target_include_directories(test_containers_common_edge_cases PRIVATE src)

# Add linking libraries
target_link_libraries(test_containers_common_interface PRIVATE containers_common)
target_link_libraries(test_containers_common_edge_cases PRIVATE containers_common)

if(BUILD_TYPE STREQUAL "debug")
    target_link_libraries(test_containers_common_interface PRIVATE -fsanitize=address)
    target_link_libraries(test_containers_common_edge_cases PRIVATE -fsanitize=address)
endif()

# Compile options
if(BUILD_TYPE STREQUAL "debug")
    add_compile_options(-std=c11 -g -Wall -Wextra -Wshadow -Wunused -Wconversion -pedantic  -fdiagnostics-color=always -fsanitize=address)
elseif(BUILD_TYPE STREQUAL "release")
    add_compile_options(-std=c11 -O2 -fPIC -D_FORTIFY_SOURCE=2 -Wl,-z,relro -Wl,-z,now 
    -Wall -Wextra -Wshadow -Wunused -Wconversion -pedantic  -fdiagnostics-color=always)
else()
    message(FATAL_ERROR "Invalid build type, use -DBUILD_TYPE and set 'release' or 'debug'")
endif()
