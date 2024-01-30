cmake_minimum_required(VERSION 3.20)
project(Controller)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES controller.cpp)

add_library(Controller STATIC ${SOURCE_FILES})

target_link_libraries(Controller Windows Painter Other Bullets Enemies Hero Player)