cmake_minimum_required(VERSION 3.20)

project(
    rubypoint-task
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)

add_executable(${PROJECT_NAME}-app app/main.cpp)
target_link_libraries(${PROJECT_NAME}-app PRIVATE ${PROJECT_NAME})

option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    FetchContent_MakeAvailable(googletest)

    add_executable(${PROJECT_NAME}-test test/main.cpp)
    target_link_libraries(${PROJECT_NAME}-test PRIVATE ${PROJECT_NAME} GTest::gtest_main)

    include(GoogleTest)
    gtest_discover_tests(${PROJECT_NAME}-test)
endif()
