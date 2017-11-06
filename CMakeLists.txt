cmake_minimum_required(VERSION 3.8)
project(Ctest)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c time.c randomEval.c)
add_executable(Ctest ${SOURCE_FILES})
add_executable(main main.c)
add_executable(time time.c)
add_executable(rand randomEval.c)