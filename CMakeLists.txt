cmake_minimum_required(VERSION 3.15)

project(dialog-generator CXX)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME}
    src/dialog-generator.cpp
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
PRIVATE Qt5::QCocoaIntegrationPlugin
    Qt5::Core
    Qt5::Widgets
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
