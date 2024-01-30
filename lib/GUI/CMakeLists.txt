cmake_minimum_required(VERSION 3.00)
project(GUI)

set(CMAKE_CXX_STANDARD 17)

include_directories(${SFML_INCLUDE_DIRS})

add_subdirectory(Windows)
add_subdirectory(Painter)
add_subdirectory(Controller)
ADD_DEPENDENCIES(Windows Painter)
ADD_DEPENDENCIES(Controller Painter Windows)
