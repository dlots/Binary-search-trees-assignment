cmake_minimum_required(VERSION 3.17)
project(seminar_lab2)

set(CMAKE_CXX_STANDARD 14)

add_executable(seminar_lab2 src/main.cpp src/trees/AbstractTree.cpp src/trees/AbstractTree.h src/trees/Treap.cpp src/trees/Treap.h src/trees/SplayTree.cpp src/trees/SplayTree.h src/trees/AVLTree.cpp src/trees/AVLTree.h src/trees/SimpleTree.cpp src/trees/SimpleTree.h src/util/RandomGenerator.cpp src/util/RandomGenerator.h test/Tests.cpp test/Tests.h graphs/Graphs.cpp graphs/Graphs.h graphs/Timer.h)