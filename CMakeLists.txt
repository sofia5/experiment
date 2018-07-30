cmake_minimum_required(VERSION 3.8)
project(Ctest)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES randomEval.c Event-based/main.c Event-based/splaytree.h Event-based/doubleLinkedList.h Ref.c "Random (Whole number priorities in interval)/splaytree.h" "Random (Whole number priorities in interval)/doubleLinkedList.h")

add_executable(Ctest ${SOURCE_FILES})
add_executable(random "Random (Whole number priorities in interval)/main.c")
add_executable(event Event-based/main.c)
add_executable(rand randomEval.c)