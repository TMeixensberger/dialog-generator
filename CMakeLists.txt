cmake_minimum_required(VERSION 3.15)

project(dialog-generator LANGUAGES CXX)

# Project default C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Qt components used by subprojects
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# Enable Qt auto tools for any Qt targets in subdirectories
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Source tree targets are placed in the src/ subdirectory
add_subdirectory(src)
