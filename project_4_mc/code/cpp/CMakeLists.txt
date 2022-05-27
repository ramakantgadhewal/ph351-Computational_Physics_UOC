cmake_minimum_required(VERSION 3.0.0)
project(mc VERSION 0.0.2)

include(CTest)
enable_testing()

add_executable(mc src/mc.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(${CMAKE_BUILD_TYPE}==Debug)
  add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set (CMAKE_CXX_FLAGS "-g")
set (CMAKE_CXX_FLAGS "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-fdiagnostics-color=always")
