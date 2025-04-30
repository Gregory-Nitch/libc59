# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(libc59_common_test_suite VERSION 1.0.0 DESCRIPTION "libc59 common unit tests.")

# Add test executables
add_executable(test_common_59_interface src/test_common_59_interface.c)
add_executable(test_common_59_edge_cases src/test_common_59_edge_cases.c)

# Add test relative paths
target_include_directories(test_common_59_interface PUBLIC src)
target_include_directories(test_common_59_interface PUBLIC ../inc)

target_include_directories(test_common_59_edge_cases PUBLIC src)
target_include_directories(test_common_59_edge_cases PUBLIC ../inc)

# Add common shared lib
target_link_libraries(test_common_59_interface libc59_common)
target_link_libraries(test_common_59_edge_cases libc59_common)

# Output to parent bin
set_target_properties(test_common_59_interface PROPERTIES  RUNTIME_OUTPUT_DIRECTORY ../../bin)
set_target_properties(test_common_59_edge_cases PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin)
