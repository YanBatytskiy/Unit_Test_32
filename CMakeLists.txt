cmake_minimum_required(VERSION 3.16)
project(unit_test_32 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
find_package(GTest CONFIG REQUIRED)
find_package(Threads REQUIRED)

add_library(core
  src/DBConnection.cpp
  src/ClassThatUsesDB.cpp
)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(tests tests/test_db.cpp)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(tests PRIVATE core GTest::gmock_main Threads::Threads)

add_test(NAME all COMMAND tests)
