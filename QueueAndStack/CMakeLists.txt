cmake_minimum_required(VERSION 3.6)
project(QueueAndStack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp MyQueue.h MyStack.h)
add_executable(QueueAndStack ${SOURCE_FILES})