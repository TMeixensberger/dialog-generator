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
    src/Generator.cpp
    src/Generator.h
    src/DialogGenerator.cpp
    src/DialogGenerator.h
    src/FactoryGenerator.cpp
    src/FactoryGenerator.h
    src/PersistorGenerator.cpp
    src/PersistorGenerator.h
    src/DataProviderGenerator.cpp
    src/DataProviderGenerator.h
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Widgets
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
