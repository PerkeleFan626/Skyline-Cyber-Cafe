cmake_minimum_required(VERSION 4.1)
project(Cafe)

set(CMAKE_CXX_STANDARD 20)

add_executable(Cafe main.cpp
        homepage.hpp
        homepage.cpp)
