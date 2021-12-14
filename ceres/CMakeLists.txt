cmake_minimum_required(VERSION 3.21)
project(ceres_tuitor)

set(CMAKE_CXX_STANDARD 14)

find_package( Ceres REQUIRED )
include_directories( ${CERES_INCLUDE_DIRS} )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_DIRS} )

add_executable(ceres_tuitor main.cpp)
target_link_libraries(ceres_tuitor ${CERES_LIBRARIES} ${OpenCV_LIBS} )