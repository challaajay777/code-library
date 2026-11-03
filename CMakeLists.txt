cmake_minimum_required(VERSION 3.16)
project(CodeLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -O2)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Test executables
file(GLOB TEST_SOURCES "tests/test_*.cpp")
foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
endforeach()
