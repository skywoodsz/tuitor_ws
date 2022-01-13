cmake_minimum_required(VERSION 3.21)

project(Tutorial VERSION 1.0) # project name and version
configure_file(TutorialConfig.h.in  TutorialConfig.h)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_INSTALL_PREFIX "./")

# add_subdirectory(MathFunctions) # 添加子目录用于编译
option(USE_MYMATH "Use tutorial provided math implementation" ON) # 自定义开关变量 变量 "说明" ON/OFF
IF(USE_MYMATH)
    add_subdirectory(MathFunctions)
    # 一般要包含lib名, lib位置
    list(APPEND EXTRA_LIBS MathFunctions) # 将元素追加到list中, 变量类型为list与set变量不同
    list(APPEND EXTRA_INCLUDES  "${PROJECT_SOURCE_DIR}/MathFunctions")
ENDIF()

add_executable(Tutorial main.cpp)

target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS}) # link libray
target_include_directories(Tutorial PUBLIC
                            "${PROJECT_BINARY_DIR}" # 编译目录位置
                            "${EXTRA_INCLUDES}"
        ) # 包含头文件路径

# ${PROJECT_SOURCE_DIR}$ 源文件位置

# add the install targets
# 若为可执行文件 安装应该指明为bin
# 在命令行中 --prefix "/home/myuser/installdir" 可指明安装路径

install(TARGETS Tutorial DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
        DESTINATION include
        )

# test
enable_testing()

# NAME: 指定测试名称(可以任意)
# COMMAND: 测试可执行程序 后为输入参数
add_test(NAME Runs COMMAND Tutorial 25)
add_test(NAME Usage COMMAND Tutorial)
# 如果测试通过/失败 输出
# PASS_REGULAR_EXPRESSION 通过
set_tests_properties(Usage
        PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number"
        )

# 打包pack
include(InstallRequiredSystemLibraries) # 包括所有的lib
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)