cmake_minimum_required(VERSION 3.10)
project(BTree2)

set(CMAKE_CXX_STANDARD 14)

add_executable(BTree2 main.cpp BTree.hpp BTNode.hpp)