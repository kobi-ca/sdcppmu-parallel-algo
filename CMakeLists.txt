cmake_minimum_required(VERSION 3.17)
project(parallel_algo)

set(CMAKE_CXX_STANDARD 17)

add_executable(parforeach parforeach.cpp)

add_executable(parforeachloop parforeachloop.cpp timer.hpp)

add_executable(countif countif.cpp timer.hpp)

add_executable(parsort parsort.cpp timer.hpp)

add_executable(parexception parexception.cpp)
