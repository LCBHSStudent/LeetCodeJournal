cmake_minimum_required(VERSION 3.15)
project(LeetCode)

set(CMAKE_CXX_STANDARD 20)

include_directories(src)

set(SOURCE src/main.cpp)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    add_compile_options(-fconcepts)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    add_compile_options(/utf-8)
endif()

add_executable(LeetCode ${SOURCE})