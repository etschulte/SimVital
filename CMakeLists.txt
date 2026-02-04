cmake_minimum_required(VERSION 3.10)

# Project Name
project(SimVital)

# Set C++ Standard (C++17 is good for modern Qt)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add your executable and source files
add_executable(SimVital main.cpp)