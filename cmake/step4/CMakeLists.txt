cmake_minimum_required(VERSION 3.22)
Project(HELLO VERSION 2.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

ADD_SUBDIRECTORY(src bin)

# install
SET(CMAKE_INSTALL_PREFIX "./install")
INSTALL(TARGETS hello
		RUNTIME	DESTINATION bin
		)
INSTALL(FILES COPYRIGHT README.md DESTINATION doc/)
INSTALL(PROGRAMS runhello.sh DESTINATION bin)
INSTALL(DIRECTORY doc/ DESTINATION share/doc/)


