# 文件生成程序
add_executable(MakeTable MakeTable.cpp)

# 用户执行命令
add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h # 输出文件位置
        COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h # COMMAND 执行工程
        DEPENDS MakeTable # 执行依赖
)


add_library(MathFunctions mysqrt.cpp
            ${CMAKE_CURRENT_BINARY_DIR}/Table.h
        )
target_include_directories(MathFunctions
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
        )

# install
# TARGETS 表明安装的为库/执行文件 其应该为相应的lib名称
# DESTINATION 表明安装路径为硬盘 后跟默认路径后的路径
install(TARGETS MathFunctions DESTINATION lib)
# FILES 表明安装的为文件
install(FILES MathFunctions.h DESTINATION include)