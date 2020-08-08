cmake_minimum_required(VERSION 3.10.2)
project(parallel_algo)

set(CMAKE_CXX_STANDARD 17)

find_package(TBB COMPONENTS tbbmalloc tbbmalloc_proxy tbb_preview)

add_executable(foreachn foreachn.cpp)

add_executable(parforeach parforeach.cpp)
target_link_libraries(parforeach tbb)

add_executable(parforeachloop parforeachloop.cpp timer.hpp)
target_link_libraries(parforeachloop tbb)

add_executable(countif countif.cpp timer.hpp)
target_link_libraries(countif tbb)

add_executable(parsort parsort.cpp timer.hpp)
target_link_libraries(parsort tbb)

add_executable(parexception parexception.cpp)

add_executable(accumulate accumulate.cpp)

add_executable(parreduce parreduce.cpp)
target_link_libraries(parreduce tbb)

add_executable(parreducefloat parreducefloat.cpp)
target_link_libraries(parreducefloat tbb)

add_executable(accumulate2 accumulate2.cpp)

add_executable(parreduce2 parreduce2.cpp)
target_link_libraries(parreduce2 tbb)

add_executable(partransformreduce partransformreduce.cpp)
target_link_libraries(partransformreduce tbb)

add_executable(dirsize dirsize.cpp)
target_link_libraries(dirsize tbb)



