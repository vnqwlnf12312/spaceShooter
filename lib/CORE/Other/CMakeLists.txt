cmake_minimum_required(VERSION 3.00)
project(Other)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES Condition.cpp
            future_config.cpp
            Movement.cpp
            userMessager.cpp)

add_library(Other STATIC ${SOURCE_FILES})
