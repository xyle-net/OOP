cmake_minimum_required(VERSION 3.10)
project(lab2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(SOURCES
    main.cpp
    money.cpp
    tests.cpp
)

add_executable(MyExecutable main.cpp money.cpp)

add_executable(lab2_tests tests.cpp)
target_include_directories(lab2_tests PRIVATE include)
set_target_properties(lab2_tests PROPERTIES OUTPUT_NAME "tests")

target_link_libraries(
  lab2_tests
  GTest::gtest_main
)

add_test(NAME MyTests COMMAND lab2_tests)