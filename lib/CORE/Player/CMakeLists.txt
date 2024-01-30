cmake_minimum_required(VERSION 3.00)
project(Player)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES Player.cpp)

add_library(Player STATIC ${SOURCE_FILES})

target_link_libraries(Player Other)