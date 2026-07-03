cmake_minimum_required(VERSION 3.15)
project(Parcial_Japet)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(Parcial_Japet
        include/ArchivoIO.h
        include/Cola.h
        include/PlanificadorMLQ.h
        include/PoliticaPlanificacion.h
        include/Proceso.h
        include/RR.h
        include/SJF.h
        src/ArchivoIO.cpp
        src/Cola.cpp
        src/PlanificadorMLQ.cpp
        src/Proceso.cpp
)
