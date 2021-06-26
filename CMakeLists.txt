cmake_minimum_required(VERSION 3.16)

project(gc_util)

SET(CRYPTO libcrypto.a)

SET(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)
SET(CMAKE_INSTALL_LIBDIR lib)
SET(CMAKE_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")  # let executable to find shared libraries

add_subdirectory(src)
add_subdirectory(test)
