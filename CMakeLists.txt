cmake_minimum_required(VERSION 3.10.2)
project(parallel_algo)

set(CMAKE_CXX_STANDARD 17)

add_executable(parforeach parforeach.cpp)

add_executable(parforeachloop parforeachloop.cpp timer.hpp)

add_executable(countif countif.cpp timer.hpp)

add_executable(parsort parsort.cpp timer.hpp)

add_executable(parexception parexception.cpp)

add_executable(accumulate accumulate.cpp)

add_executable(parreduce parreduce.cpp)

add_executable(parreducefloat parreducefloat.cpp)

add_executable(accumulate2 accumulate2.cpp)

add_executable(parreduce2 parreduce2.cpp)

add_executable(partransformreduce partransformreduce.cpp)

add_executable(dirsize dirsize.cpp)


