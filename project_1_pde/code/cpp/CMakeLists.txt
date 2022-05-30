cmake_minimum_required(VERSION 3.0.0)
project(pde VERSION 0.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(pde_1d src/pde_1d.cpp)
add_executable(pde_2d src/pde_2d.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(${CMAKE_BUILD_TYPE}=="Debug")
  add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
endif()
