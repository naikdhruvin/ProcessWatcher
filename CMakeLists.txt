cmake_minimum_required(VERSION 3.10)
project(processWatcher)
#C++ compiler options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

if(MSVC)
    add_compile_options(
        $<$<CONFIG:>:/MT> #---------|
        $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
        $<$<CONFIG:Release>:/MT> #--|
    )
endif()

# include CalculationEngine library
set(ProcessWatchEngine_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ProcessWatchEngine)
add_subdirectory(ProcessWatchEngine)

include_directories(${ProcessWatchEngine_INCLUDE_DIR}/include)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable(${CMAKE_PROJECT_NAME}_run ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}_run ProcessWatchEngine)
if (UNIX)
    target_link_libraries(${CMAKE_PROJECT_NAME}_run -lprocps)
endif (UNIX)

ADD_DEPENDENCIES(${CMAKE_PROJECT_NAME}_run ProcessWatchEngine)
add_subdirectory(tests)

# Doxygen Build
option(BUILD_DOC "Build Documentation" ON)
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR ${CMAKE_SOURCE_DIR}/build/docs)
    if(NOT EXISTS ${BUILD_DOC_DIR})
        file(MAKE_DIRECTORY ${BUILD_DOC_DIR})
    endif()
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)
