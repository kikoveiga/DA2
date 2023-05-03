cmake_minimum_required(VERSION 3.25)
project(DA2)

set(CMAKE_CXX_STANDARD 14)

add_executable(DA2
        src/main.cpp headers/Graph.h src/Graph.cpp headers/Utils.h src/Utils.cpp)
