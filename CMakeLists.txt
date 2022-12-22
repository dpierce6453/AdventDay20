cmake_minimum_required(VERSION 3.23)
project(AdventDay20)

set(CMAKE_CXX_STANDARD 20)

add_executable(AdventDay20 main.cpp mixer.cpp mixer.h testfiles.h)


enable_testing()
add_subdirectory(Tests)