# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(vec_59_test_suite VERSION 1.0.0 DESCRIPTION "Vector unit tests")

# Add test executables
add_executable(test_vec_59_interface src/test_vec_59_interface.c)
add_executable(test_vec_59_edge_cases src/test_vec_59_edge_cases.c)

# Add test relative paths
target_include_directories(test_vec_59_interface PUBLIC src)
target_include_directories(test_vec_59_interface PUBLIC ../inc)
target_include_directories(test_vec_59_interface PUBLIC ../../common/inc)
target_include_directories(test_vec_59_interface PUBLIC ../../../common/inc)

target_include_directories(test_vec_59_edge_cases PUBLIC src)
target_include_directories(test_vec_59_edge_cases PUBLIC ../inc)
target_include_directories(test_vec_59_edge_cases PUBLIC ../../common/inc)
target_include_directories(test_vec_59_edge_cases PUBLIC ../../../common/inc)

# Add vec shared lib
target_link_libraries(test_vec_59_interface vec_59)
target_link_libraries(test_vec_59_edge_cases vec_59)


# Output to parent bin
set_target_properties(test_vec_59_interface PROPERTIES  RUNTIME_OUTPUT_DIRECTORY ../../bin)
set_target_properties(test_vec_59_edge_cases PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin)
