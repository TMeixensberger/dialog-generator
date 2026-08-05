cmake_minimum_required(VERSION 3.15)

project(dialog-generator CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME}
    src/MainWindow.ui
    src/dialog-generator.cpp
    src/Parser.cpp
    src/Parser.h
    src/UiFile.h
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
#PRIVATE Qt5::QCocoaIntegrationPlugin
    Qt5::Core
    Qt5::Widgets
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
