cmake_minimum_required(VERSION 2.8.9)
project(CalculationEngine)
#add the library
#C++ compiler options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


include_directories(include)

file(GLOB CalculationEngine_headers include/*.h)
file(GLOB CalculationEngine_sources src/*.cpp)


add_library(CalculationEngine STATIC ${CalculationEngine_headers} ${CalculationEngine_sources})

