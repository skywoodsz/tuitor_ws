cmake_minimum_required(VERSION 3.21)
project(QPOASES)

set(CMAKE_CXX_STANDARD 14)

include_directories("/usr/local/include")

add_executable(QPOASES main.cpp)
target_link_libraries(QPOASES libqpOASES.a)

