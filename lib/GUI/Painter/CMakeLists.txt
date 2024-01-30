cmake_minimum_required(VERSION 3.20)
project(Painter)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES Painter.cpp PainterMainMenu.cpp PainterLevelWindow.cpp PainterChooseWindow.cpp PainterShopWindow.cpp)

add_library(Painter STATIC ${SOURCE_FILES})

target_link_libraries(Painter Bullets Enemies Hero Other Player)
