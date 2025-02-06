cmake_minimum_required(VERSION 3.29)
project(Ambulance_Simulator_System)

set(CMAKE_CXX_STANDARD 20)

add_executable(Ambulance_Simulator_System main.cpp
        Patient.cpp
        Patient.h
        Car.cpp
        Car.h
        EPQueue.cpp
        EPQueue.h
        NPQueue.cpp
        NPQueue.h
        SPQueue.cpp
        SPQueue.h
        NCQueue.cpp
        NCQueue.h
        SCQueue.cpp
        SCQueue.h
        Out_Back.cpp
        Out_Back.h
        Hospital.cpp
        Hospital.h
        InputReader.cpp
        InputReader.h
        Organizer.cpp
        Organizer.h)
