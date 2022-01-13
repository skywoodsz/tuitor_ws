# CMake generated Testfile for 
# Source directory: /home/skywoodsz/tuitor_ws/cmake/step2
# Build directory: /home/skywoodsz/tuitor_ws/cmake/step2/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[Runs]=] "/home/skywoodsz/tuitor_ws/cmake/step2/cmake-build-debug/Tutorial" "25")
set_tests_properties([=[Runs]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/skywoodsz/tuitor_ws/cmake/step2/CMakeLists.txt;44;add_test;/home/skywoodsz/tuitor_ws/cmake/step2/CMakeLists.txt;0;")
add_test([=[Usage]=] "/home/skywoodsz/tuitor_ws/cmake/step2/cmake-build-debug/Tutorial")
set_tests_properties([=[Usage]=] PROPERTIES  PASS_REGULAR_EXPRESSION "Usage:.*number" _BACKTRACE_TRIPLES "/home/skywoodsz/tuitor_ws/cmake/step2/CMakeLists.txt;45;add_test;/home/skywoodsz/tuitor_ws/cmake/step2/CMakeLists.txt;0;")
subdirs("MathFunctions")
