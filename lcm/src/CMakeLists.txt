cmake_minimum_required(VERSION 3.10)
project(LCM)

set(CMAKE_CXX_STANDARD 11)
find_package(lcm)
include_directories("../type")

add_executable(LCM_Client send_msg.cpp)
target_link_libraries(LCM_Client lcm)

add_executable(LCM_Server listener.cpp)
target_link_libraries(LCM_Server lcm)
