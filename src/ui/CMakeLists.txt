cmake_minimum_required(VERSION 3.15)

# UI executable (links against the generator library)
set(UI_SOURCES
    main.cpp
)

set(UI_FILES
    MainWindow.ui
)

add_executable(${PROJECT_NAME}
    ${UI_SOURCES}
    ${UI_FILES}
)

# ensure the executable finds headers in the ui directory
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# link against Qt widgets and the generator library
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets generator)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
