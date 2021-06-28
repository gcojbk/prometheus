cmake_minimum_required(VERSION 3.16)

project(gc_util)

add_definitions(-std=c++17)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)
SET(CMAKE_INSTALL_LIBDIR lib)
SET(CMAKE_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")  # let executable to find shared libraries

SET(CRYPTO libcrypto.a)

add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test(NAME Test COMMAND Test)
# set_tests_properties (Test PROPERTIES FAIL_REGULAR_EXPRESSION "Failure")
