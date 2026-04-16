cmake_minimum_required(VERSION 3.20)

project(
    rubypoint-task
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED 20)

add_executable(${PROJECT_NAME} main.cpp)
