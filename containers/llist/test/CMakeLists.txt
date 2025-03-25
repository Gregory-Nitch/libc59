# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(test_llist_59 VERSION 1.0.0 DESCRIPTION "Linked list unit tests")

# Add test executable
add_executable(test_llist_59 src/test_llist_59.c)

# Add test relative paths
target_include_directories(test_llist_59 PUBLIC src)
target_include_directories(test_llist_59 PUBLIC ../inc)
target_include_directories(test_llist_59 PUBLIC ../../../common/inc)
