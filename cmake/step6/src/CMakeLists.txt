INCLUDE_DIRECTORIES(~/tuitor_ws/cmake/step5/build/install/include/hello)
LINK_DIRECTORIES(~/tuitor_ws/cmake/step5/build/install/lib)
ADD_EXECUTABLE(main main.cpp)
TARGET_LINK_LIBRARIES(main hello)
