cmake_minimum_required(VERSION 3.8)
project(Ctest)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES randomEval.c "Pending event set/main.c" "Pending event set/splaytree.h" "Pending event set/doubleLinkedList.h" Ref.c "Ready-queue/splaytree.h" "Ready-queue/doubleLinkedList.h")

add_executable(Ctest ${SOURCE_FILES})
add_executable(ready "Ready-queue/main.c")
add_executable(event "Pending event set/main.c")
add_executable(rand randomEval.c)