include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Unit_Tests_run
    test_example.cpp
)

target_link_libraries(Unit_Tests_run gtest gtest_main)
target_link_libraries(Unit_Tests_run ProcessWatchEngine)
if (UNIX)
    target_link_libraries(Unit_Tests_run -lprocps)
endif (UNIX)
