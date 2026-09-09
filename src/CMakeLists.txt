cmake_minimum_required(VERSION 3.15)

# UI executable (links against the generator library)
set(UI_SOURCES
    ui/main.cpp
    #ui/MainWindow.cpp
    #ui/MainWindow.h
    #ui/ProjectTableModel.cpp
    #ui/ProjectTableModel.h
    dynamic/DDFactory.cpp
    dynamic/DDFactory.hpp
    dynamic/DDDataProvider.cpp
    dynamic/DDDataProvider.hpp
    dynamic/DynamicDialog.cpp
    dynamic/DynamicDialog.hpp
    dynamic/DynamicDialogPersistor.cpp
    dynamic/DynamicDialogPersistor.hpp
    dynamic/IDynamicDialogDataProvider.hpp
    dynamic/Operations.hpp
    dynamic/widgets/Square.cpp
    dynamic/widgets/Square.hpp
    dynamic/widgets/Sine.cpp
    dynamic/widgets/Sine.hpp
)

set(UI_FILES
    ui/MainWindow.ui
    dynamic/DynamicDialog.ui
    dynamic/widgets/Square.ui
    dynamic/widgets/Sine.ui
)

add_executable(${PROJECT_NAME}
    ${UI_SOURCES}
    ${UI_FILES}
)

# ensure the executable finds headers in the ui directory
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# link against Qt widgets and the generator library
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
