cmake_minimum_required(VERSION 3.10)
project(lab)

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

add_executable(MyExecutable main.cpp)

add_executable(MyTests tests.cpp)

target_link_libraries(MyTests gtest gtest_main)

add_test(NAME MyTests COMMAND MyTests)