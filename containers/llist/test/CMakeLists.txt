# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(llist_59_test_suite VERSION 1.0.0 DESCRIPTION "Linked list unit tests")

# Add test executables
add_executable(test_llist_59_interface src/test_llist_59_interface.c)

add_executable(test_llist_59_edge_cases src/test_llist_59_edge_cases.c)

add_executable(test_llist_node_59_interface src/test_llist_node_59_interface.c)

add_executable(test_llist_node_59_edge_cases src/test_llist_node_59_edge_cases.c)

# Add test relative paths
target_include_directories(test_llist_59_interface PUBLIC src)
target_include_directories(test_llist_59_interface PUBLIC ../inc)
target_include_directories(test_llist_59_interface PUBLIC ../../../common/inc)

target_include_directories(test_llist_59_edge_cases PUBLIC src)
target_include_directories(test_llist_59_edge_cases PUBLIC ../inc)
target_include_directories(test_llist_59_edge_cases PUBLIC ../../../common/inc)

target_include_directories(test_llist_node_59_interface PUBLIC src)
target_include_directories(test_llist_node_59_interface PUBLIC ../inc)
target_include_directories(test_llist_node_59_interface PUBLIC ../../../common/inc)

target_include_directories(test_llist_node_59_edge_cases PUBLIC src)
target_include_directories(test_llist_node_59_edge_cases PUBLIC ../inc)
target_include_directories(test_llist_node_59_edge_cases PUBLIC ../../../common/inc)

# Add llist shared lib
target_link_libraries(test_llist_59_interface llist_59)

target_link_libraries(test_llist_59_edge_cases llist_59)

target_link_libraries(test_llist_node_59_interface llist_59)

target_link_libraries(test_llist_node_59_edge_cases llist_59)


# Output to parent bin
set_target_properties(test_llist_59_interface PROPERTIES  RUNTIME_OUTPUT_DIRECTORY ../../bin)

set_target_properties(test_llist_59_edge_cases PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin)

set_target_properties(test_llist_node_59_interface PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin)

set_target_properties(test_llist_node_59_edge_cases PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../../bin)
