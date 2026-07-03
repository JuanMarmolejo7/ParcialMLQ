cmake_minimum_required(VERSION 3.15)
project(Parcial_Japet)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(Parcial_Japet
        src/main.cpp
        src/Proceso.cpp
        src/RR.cpp
        src/SJF.cpp
        src/Cola.cpp
        src/PlanificadorMLQ.cpp
        src/ArchivoIO.cpp
        include/ArchivoIO.h
        include/ArchivoIO.h
)
