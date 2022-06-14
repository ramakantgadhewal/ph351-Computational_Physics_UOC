cmake_minimum_required(VERSION 3.0.0)
project(mockexam VERSION 0.1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(problem_head "src/mock_exam")

add_executable(mock_1 ${problem_head}_1.cpp ${problem_head}_1.h)
add_executable(mock_2 ${problem_head}_2.cpp ${problem_head}_2.h)
add_executable(mock_3 ${problem_head}_3.cpp ${problem_head}_3.h)
add_executable(mock_4 ${problem_head}_4.cpp ${problem_head}_4.h)

include_directories(${CMAKE_SOURCE_DIR}/../../../universal_code/cpp/src)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(${CMAKE_BUILD_TYPE}=="Debug")
  add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
endif()
