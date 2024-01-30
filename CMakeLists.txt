cmake_minimum_required(VERSION 3.00)
project(SPACERETARDS)

set(CMAKE_CXX_STANDARD 17)

set(SPACERETARDS_RUNTIME_OUTPUT_INTDIR ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/bin/)
set(SPACERETARDS_LIBRARY_OUTPUT_INTDIR ${CMAKE_CURRENT_BINARY_DIR}/lib)

add_executable(SPACERETARDS main.cpp)

ADD_COMPILE_DEFINITIONS(SRC_DIR=\"${CMAKE_SOURCE_DIR}\")

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

set(SPACERETARDS_MAIN_SRC_DIR     ${CMAKE_CURRENT_SOURCE_DIR})
set(SPACERETARDS_MAIN_INCLUDE_DIR ${SPACERETARDS_MAIN_SRC_DIR}/include)
set(SPACERETARDS_MAIN_LIB_DIR     ${SPACERETARDS_MAIN_SRC_DIR}/lib)
set(SPACERETARDS_BINARY_DIR       ${CMAKE_CURRENT_BINARY_DIR})

link_libraries(sfml-graphics sfml-window sfml-audio sfml-network sfml-system)

include_directories(${SPACERETARDS_MAIN_INCLUDE_DIR})

add_subdirectory(lib)
IF(TESTS_REQUIRED)
    message("tests builded")
    add_subdirectory(${SPACERETARDS_MAIN_SRC_DIR}/GTestDir/$ENV{GOOGLE_TEST_DIR})
    add_subdirectory(tests)
endif ()
target_link_libraries(SPACERETARDS Bullets Enemies Hero Other Controller Painter Windows)

