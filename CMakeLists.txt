cmake_minimum_required(VERSION 3.15)
project(dialog-generator CXX)



add_executable(dialog-generator src/dialog-generator.cpp src/main.cpp)



install(TARGETS dialog-generator DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
