cmake_minimum_required(VERSION 3.10)

# Project name
project(TrafficSimulation)

# Set the standard for C++ to 11
set(CMAKE_CXX_STANDARD 11)

# Include the header directory
include_directories(include)

# Find and include SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Add the executable
add_executable(TrafficSimulation src/TrafficSimulation.cpp src/Car.cpp src/TrafficLight.cpp)

# Link SFML libraries
target_link_libraries(TrafficSimulation sfml-system sfml-window sfml-graphics)
