cmake_minimum_required(VERSION 3.00)
project(Enemies)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES EnemyFactory.cpp
        Enemies.cpp)

add_library(Enemies STATIC ${SOURCE_FILES})

target_link_libraries(Enemies Other Bullets)