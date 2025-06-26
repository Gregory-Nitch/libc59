# Set cmake version
cmake_minimum_required(VERSION 3.22.1)

#Set project name, version, description
project(libc59 VERSION 1.0.0 DESCRIPTION "libc59 libraries" LANGUAGES C)


# Compile options
if(BUILD_TYPE STREQUAL "debug")
    add_compile_options(-std=c11 -g -Wall -Wextra -Wshadow -Wunused -Wconversion -pedantic  -fdiagnostics-color=always -fsanitize=address)
elseif(BUILD_TYPE STREQUAL "release")
    add_compile_options(-std=c11 -O2 -fPIC -D_FORTIFY_SOURCE=2 -Wl,-z,relro -Wl,-z,now 
    -Wall -Wextra -Wshadow -Wunused -Wconversion -pedantic  -fdiagnostics-color=always)
else()
    message(FATAL_ERROR "Invalid build type, use -DBUILD_TYPE and set 'release' or 'debug'")
endif()

# Set a global build directory for all sub-projects
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add subdirectories for each library
add_subdirectory(common)
add_subdirectory(containers/common)
add_subdirectory(containers/dlist)
add_subdirectory(containers/llist)
add_subdirectory(containers/vec)
add_subdirectory(containers/hash_map)

# Get them tests running
include(CTest)

# Add test suite with valgrind -> # -s = show suppressed errors
add_test(NAME test_common_interface
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_common_interface>
)
set_tests_properties(test_common_interface
    PROPERTIES PASS_REGULAR_EXPRESSION
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_common_edge_cases
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_common_edge_cases>
)
set_tests_properties(test_common_edge_cases
    PROPERTIES PASS_REGULAR_EXPRESSION
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_containers_common_interface
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_containers_common_interface>
)
set_tests_properties(test_containers_common_interface
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_containers_common_edge_cases
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_containers_common_edge_cases>
)
set_tests_properties(test_containers_common_edge_cases
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_dlist_interface
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_dlist_interface>
)
set_tests_properties(test_dlist_interface
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_dlist_edge_cases
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_dlist_edge_cases>
)
set_tests_properties(test_dlist_edge_cases
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_dlist_node_interface
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_dlist_node_interface>
)
set_tests_properties(test_dlist_node_interface
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_dlist_node_edge_cases
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_dlist_node_edge_cases>
)
set_tests_properties(test_dlist_node_edge_cases
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_hash_map_interface
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_hash_map_interface>
)
set_tests_properties(test_hash_map_interface
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_hash_map_edge_cases
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_hash_map_edge_cases>
)
set_tests_properties(test_hash_map_edge_cases
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_llist_interface
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_llist_interface>
)
set_tests_properties(test_llist_interface
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_llist_edge_cases
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_llist_edge_cases>
)
set_tests_properties(test_llist_edge_cases
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_llist_node_interface
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_llist_node_interface>
)
set_tests_properties(test_llist_node_interface
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_llist_node_edge_cases
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_llist_node_edge_cases>
)
set_tests_properties(test_llist_node_edge_cases
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_vec_interface
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_vec_interface>
)
set_tests_properties(test_vec_interface
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

add_test(NAME test_vec_edge_cases
    COMMAND valgrind --leak-check=full --show-leak-kinds=all --verbose -s
    $<TARGET_FILE:test_vec_edge_cases>
)
set_tests_properties(test_vec_edge_cases
    PROPERTIES PASS_REGULAR_EXPRESSION 
    ".*in use at exit: 0 bytes in 0 blocks.*0 errors from 0 contexts.*suppressed: 0 from 0.*"
)

#########################################################################
#                           Installation Rules                          #
#########################################################################

# Get GNU install variables
include(GNUInstallDirs)

# Install shared libraries AND define the export set 'libc59Targets'
install(TARGETS
    common
    containers_common
    dlist
    llist
    vec
    hash_map
    EXPORT libc59Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libc59
)

# Install public headers
install(DIRECTORY common/inc/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libc59
    FILES_MATCHING PATTERN "*.h"
)
install(DIRECTORY containers/common/inc/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libc59
    FILES_MATCHING PATTERN "*.h"
)
install(DIRECTORY containers/dlist/inc/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libc59
    FILES_MATCHING PATTERN "*.h"
)
install(DIRECTORY containers/llist/inc/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libc59
    FILES_MATCHING PATTERN "*.h"
)
install(DIRECTORY containers/vec/inc/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libc59
    FILES_MATCHING PATTERN "*.h"
)
install(DIRECTORY containers/hash_map/inc/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/libc59
    FILES_MATCHING PATTERN "*.h"
)

# CMake package configuration files and target exports
# This will now correctly install the 'libc59Targets' export set
install(EXPORT libc59Targets
    NAMESPACE libc59::
    FILE libc59Targets.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libc59
)
