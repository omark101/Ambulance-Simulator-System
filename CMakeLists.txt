cmake_minimum_required(VERSION 3.29)
project(Ambulance_Simulator_System)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)  # Include header files

file(GLOB SOURCES "src/*.cpp")  # Find all .cpp files

add_executable(Ambulance_Simulator_System ${SOURCES})
