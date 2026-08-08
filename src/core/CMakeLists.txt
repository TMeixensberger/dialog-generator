cmake_minimum_required(VERSION 3.15)

set(CORE_SOURCES
    Project.cpp
    ProjectFile.cpp
    Settings.cpp
)

add_library(core STATIC ${CORE_SOURCES})

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../generator
)

target_link_libraries(core PUBLIC Qt5::Core)

install(TARGETS core
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
