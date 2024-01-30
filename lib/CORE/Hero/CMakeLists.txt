cmake_minimum_required(VERSION 3.00)
project(Hero)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES Hero.cpp)

add_library(Hero STATIC ${SOURCE_FILES})

target_link_libraries(Hero Bullets Other)