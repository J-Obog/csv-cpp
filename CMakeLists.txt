cmake_minimum_required(VERSION 3.5)
project(csvcpp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
option(BUILD_TESTS "Build the tests directory" ON)

if(BUILD_TESTS)
    message(STATUS "Building project tests")
    add_subdirectory(tests)
endif()