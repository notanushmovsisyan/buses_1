cmake_minimum_required(VERSION 3.0)
project(buses_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(buses_1 ${SOURCES})