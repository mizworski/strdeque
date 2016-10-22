cmake_minimum_required(VERSION 3.6)
project(zadanie2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -c -Wall -O2 -std=c++14")

set(SOURCE_FILES strdeque.cc strdeque.h strdequeconst.cc strdequeconst.h cstrdeque cstrdequeconst)
add_executable(zadanie2 ${SOURCE_FILES})