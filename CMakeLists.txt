cmake_minimum_required(VERSION 3.8)
project(Ctest)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES Event-based/doubleLinkedList.c randomEval.c "Random (Whole number priorities in interval)/doubleLinkedList.c" "Random (Whole number priorities in interval)/splaytree.c" Event-based/main.c)
add_executable(Ctest ${SOURCE_FILES} Event-based/splaytree.c "Random (Whole number priorities in interval)/main.c")
add_executable(linkedList "Random (Whole number priorities in interval)/doubleLinkedList.c")
add_executable(splaytree "Random (Whole number priorities in interval)/splaytree.c")

add_executable(linkedListEvent Event-based/doubleLinkedList.c)
add_executable(splaytreeEvent Event-based/splaytree.c)

add_executable(rand randomEval.c)