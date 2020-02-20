cmake_minimum_required(VERSION 3.15)
project(datastructure)

set(CMAKE_CXX_STANDARD 14)



add_executable(datastructure main.cpp array.hpp array.cpp ArrayStack.cpp ArrayStack.hpp FastArrayStack.cpp FastArrayStack.hpp utils.h ArrayQueue.cpp ArrayQueue.h ArrayDeque.cpp ArrayDeque.h DualArrayDeque.cpp DualArrayDeque.h RootishArrayStack.cpp RootishArrayStack.h SLList.cpp SLList.h DLList.cpp DLList.h SEList.cpp SEList.h)