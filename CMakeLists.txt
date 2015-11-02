cmake_minimum_required(VERSION 3.3)
project(Knapsack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES addarrays.cpp)
add_executable(Knapsack ${SOURCE_FILES})