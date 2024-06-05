cmake_minimum_required(VERSION 2.8.9)
project(ProcessWatchEngine)
#add the library
#C++ compiler options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


include_directories(include)

file(GLOB ProcessWatchEngine_headers include/*.h)
file(GLOB ProcessWatchEngine_sources src/*.cpp)


add_library(ProcessWatchEngine STATIC ${ProcessWatchEngine_headers} ${ProcessWatchEngine_sources})

