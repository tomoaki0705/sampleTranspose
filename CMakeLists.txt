cmake_minimum_required(VERSION 2.8)

project(sampleTranspose)

set(CMAKE_CXX_FLAGS "-O3 -mfpu=neon-fp16")

add_executable(sampleTranspose main.cpp)
