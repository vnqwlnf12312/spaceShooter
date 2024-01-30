cmake_minimum_required(VERSION 3.00)
project(Windows)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES chooseWindow.cpp
        levels.cpp
        MainMenu.cpp
        shopWindow.cpp
        window.cpp)

add_library(Windows STATIC ${SOURCE_FILES})

target_link_libraries(Windows Enemies Bullets Other Hero Painter Player)