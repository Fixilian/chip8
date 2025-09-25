cmake_minimum_required(VERSION 3.13)
project(chip8 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_CXX_EXTENSIONS)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

option(CHIP8_TESTING "Unit tests are enable" OFF)

include_directories("src/")

add_subdirectory(external)

add_subdirectory(src)

if(NOT CHIP8_TESTING)
  message(STATUS "Unit tests are disable")
else()
  enable_testing()
  add_subdirectory(test)
endif()
