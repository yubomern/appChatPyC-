cmake_minimum_required(VERSION 3.20)

project(tests)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  hello_test
  hello_test.cpp
)
target_link_libraries(
  hello_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)

if(TARGET Tutorial)
  add_test(
    NAME Tutorial.Output
    COMMAND
      ${CMAKE_COMMAND}
      "-DTUTORIAL_EXECUTABLE=$<TARGET_FILE:Tutorial>"
      -P "${CMAKE_CURRENT_SOURCE_DIR}/test_tutorial.cmake"
  )
endif()