cmake_minimum_required(VERSION 3.00)
project(SPACESHOOTER)

set(CMAKE_CXX_STANDARD 17)

set(SPACESHOOTER_RUNTIME_OUTPUT_INTDIR ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/bin/)
set(SPACESHOOTER_LIBRARY_OUTPUT_INTDIR ${CMAKE_CURRENT_BINARY_DIR}/lib)

add_executable(SPACESHOOTER main.cpp)

ADD_COMPILE_DEFINITIONS(SRC_DIR=\"${CMAKE_SOURCE_DIR}\")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

set(SPACESHOOTER_MAIN_SRC_DIR     ${CMAKE_CURRENT_SOURCE_DIR})
set(SPACESHOOTER_MAIN_INCLUDE_DIR ${SPACESHOOTER_MAIN_SRC_DIR}/include)
set(SPACESHOOTER_MAIN_LIB_DIR     ${SPACESHOOTER_MAIN_SRC_DIR}/lib)
set(SPACESHOOTER_BINARY_DIR       ${CMAKE_CURRENT_BINARY_DIR})

link_libraries(sfml-graphics sfml-window sfml-audio sfml-network sfml-system)

include_directories(${SPACESHOOTER_MAIN_INCLUDE_DIR})

add_subdirectory(lib)
IF(TESTS_REQUIRED)
    message("tests builded")
    add_subdirectory(${SPACESHOOTER_MAIN_SRC_DIR}/GTestDir/$ENV{GOOGLE_TEST_DIR})
    add_subdirectory(tests)
endif ()
target_link_libraries(SPACESHOOTER Bullets Enemies Hero Other Controller Painter Windows)

