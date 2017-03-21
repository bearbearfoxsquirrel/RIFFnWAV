cmake_minimum_required(VERSION 3.6)
project(Practical_14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp RIFF.h WAV.h WAV.cpp RIFF.cpp)
add_executable(Practical_14 ${SOURCE_FILES})