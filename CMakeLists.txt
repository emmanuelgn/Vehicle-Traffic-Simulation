cmake_minimum_required(VERSION 3.10)

# Project name
project(TrafficSimulation)

# Set the standard for C++ to 11
set(CMAKE_CXX_STANDARD 11)

# Include the header directory
include_directories(include)

# Add the executable
add_executable(TrafficSimulation src/main.cpp src/Car.cpp)