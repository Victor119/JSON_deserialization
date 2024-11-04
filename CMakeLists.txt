cmake_minimum_required(VERSION 3.14)
project(JsonExecProject)

# C++ options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# GoogleTest (From documentation)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # For Windows
FetchContent_MakeAvailable(googletest)

# Main executable
add_executable(json_eval src/main.cpp src/json.cpp)

# Test executable
enable_testing()
add_executable(json_eval_tests src/json.cpp tests/tests.cpp)
target_link_libraries(json_eval_tests gtest_main)
include(GoogleTest)
gtest_discover_tests(json_eval_tests)
