cmake_minimum_required(VERSION 3.15)

# Generator library (parsing + generation logic)
set(GENERATOR_SOURCES
    Parser.cpp
    Generator.cpp
    DialogGenerator.cpp
    FactoryGenerator.cpp
    PersistorGenerator.cpp
    DataProviderGenerator.cpp
)

add_library(generator STATIC ${GENERATOR_SOURCES})

target_include_directories(generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(generator PUBLIC Qt5::Core)

install(TARGETS generator
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
