cmake_minimum_required(VERSION 3.15)

# Generator library (parsing + generation logic)
set(GENERATOR_SOURCES
    Parser.cpp
    IGenerator.cpp
    Generator.cpp
    gens/DialogGenerator.cpp
    gens/FactoryGenerator.cpp
    gens/PersistorGenerator.cpp
    gens/DataProviderGenerator.cpp
)

add_library(generator STATIC ${GENERATOR_SOURCES})

# expose headers at generator root and gens/ subdirectory
target_include_directories(generator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/gens)

target_link_libraries(generator PUBLIC Qt5::Core Qt5::Widgets)

install(TARGETS generator
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
