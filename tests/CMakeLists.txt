project(Tests)


add_executable(TESTCODE BulletTest.cpp EnemyTest.cpp)

find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(TESTCODE ${GTEST_LIBRARIES})
target_include_directories(TESTCODE PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(TESTCODE PRIVATE ${CMAKE_BINARY_DIR})

target_link_libraries(TESTCODE gtest_main Bullets Enemies Other)
add_dependencies(TESTCODE Bullets Other)
target_include_directories(TESTCODE PRIVATE ${CMAKE_SOURCE_DIR})
