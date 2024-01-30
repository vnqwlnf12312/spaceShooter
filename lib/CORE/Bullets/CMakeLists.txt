cmake_minimum_required(VERSION 3.00)
project(Bullets)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES BulletFactory.cpp
        Bullets.cpp)

add_library(Bullets STATIC ${SOURCE_FILES})

target_link_libraries(Bullets Other)