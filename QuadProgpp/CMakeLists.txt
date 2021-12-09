cmake_minimum_required(VERSION 3.21)
project(QuadProgpp_tuitor)

set(CMAKE_CXX_STANDARD 11)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})
include_directories(/usr/local/include/QuadProg++)

add_executable(QuadProgpp_tuitor main.cpp)

target_link_libraries(QuadProgpp_tuitor libquadprog.a)