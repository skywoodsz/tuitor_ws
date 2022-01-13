add_library(MathFunctions mysqrt.cpp)

# install
# TARGETS 表明安装的为库/执行文件 其应该为相应的lib名称
# DESTINATION 表明安装路径为硬盘 后跟默认路径后的路径
install(TARGETS MathFunctions DESTINATION lib)
# FILES 表明安装的为文件
install(FILES MathFunctions.h DESTINATION include)