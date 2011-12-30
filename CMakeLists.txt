cmake_minimum_required(VERSION 2.8)

# Name of the cmake project.
project(MathLibraryTest)

# All libraries are header only.
include_directories(lib/cml-1_0_2)
include_directories(lib/eigen-eigen-13a11181fc5a)
include_directories(lib/glm-0.9.3.B)

# Add a test program.
add_executable(Main src/Main.cpp)
