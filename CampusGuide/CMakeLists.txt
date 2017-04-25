cmake_minimum_required(VERSION 3.6)
project(project4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    include/Graph.hpp
    include/Guide_service.hpp
    include/Guide_UI.hpp
    include/Spot.hpp
    include/Storage.hpp
    src/Graph.cpp
    src/Guide_service.cpp
    src/Guide_UI.cpp
    src/main.cpp
    src/Spot.cpp
    src/Storage.cpp)

add_executable(project4 ${SOURCE_FILES})