cmake_minimum_required(VERSION 3.16)

project(SimVital VERSION 0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt Boilerplate (Required for Signals/Slots)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt
set(CMAKE_PREFIX_PATH "/home/evan/Qt/6.10.2/gcc_64")

# Find Packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Charts SerialPort Multimedia)

add_subdirectory(core)
add_subdirectory(app)