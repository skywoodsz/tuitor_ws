## cmake使用

#### 1. 平常

1.  指定cmake版本

    `cmake_minimum_required(VERSION 3.21)`

2.  指定工程与版本

    `project(Tutorial VERSION 1.0)`

    *Notes：*可由.h.in文件获取VERSION

    ```cmake
    # 自定义.h.in文件 自动生成.h文件
    # 可通过包含该.h文件获取版本号
    # .h.in文件如下： 宏变量可自定义 @xxx@为获取的可变参数，可自定义名称
    # #define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR@
    # #define Tutorial_VERSION_MINOR @Tutorial_VERSION_MINOR@
    configure_file(TutorialConfig.h.in  TutorialConfig.h) 
    ```

3.  定义cpp标准

    `set(CMAKE_CXX_STANDARD 11)`

    `set(CMAKE_CXX_STANDARD_REQUIRED True)`

4.  生成可执行文件

    `add_executable(Tutorial main.cpp)`

5.  连接库(若无库则无需连接)

    `target_link_libraries(Tutorial ${EXTRA_LIBS})`

6.  包含include文件地址

    ```cmake
    target_include_directories(Tutorial PUBLIC
                                "${PROJECT_BINARY_DIR}" # 编译目录位置
                                "${EXTRA_INCLUDES}"
            ) # 包含头文件路径
    ```

*Notes：*宏变量定义

```
 "${PROJECT_BINARY_DIR}" # 工程编译目录位置
 "${PROJECT_SOURCE_DIR}" # 工程源文件位置
 ${CMAKE_CURRENT_BINARY_DIR} 当前编译目录位置
 ${CMAKE_CURRENT_SOURCE_DIR} 当前源文件目录位置
```

#### 2. 生成库

在库文件夹下添加新cmakelists有命令

1.  生成库(.a 静态)

    ```cmake
    add_library(MathFunctions STATIC mysqrt.cpp
                ${CMAKE_CURRENT_BINARY_DIR}/Table.h
            )
    ```

2.  生成库(.so 动态)

    ```cmake
    ADD_LIBRARY(hello SHARED ${LIBHELLO_SRC})
    # VERSION 指定版本号 SOVERSION 指定api号
    SET_TARGET_PROPERTIES(hello PROPERTIES VERSION 1.2 SOVERSION 1)
    # 重命名
    SET_TARGET_PROPERTIES(hello_static PROPERTIES OUTPUT_NAME "hello")
    ```

3.  连接库(无可省略)

    target_link_libraries(MathFunctions ${EXTRA_LIBS})

4.  添加include地址

    ```cmake
    target_include_directories(MathFunctions
            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
            PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
            )
    ```

    `PRIVATE`表示私有，仅该库可以调用该文件夹，上层调用程序则不可调用

#### 3. 添加库

在顶层文件夹下的cmakelists中

1.   添加库子文件夹

        ```cmake
    add_subdirectory(MathFunctions)
       ```

2.  添加库

    -   可直接通过lib工程名添加

        ```cmake
        add_executable(Tutorial tutorial.cxx)
        # 连接库
        target_link_libraries(Tutorial PUBLIC MathFunctions)
        # 添加库include文件夹
        target_include_directories(Tutorial PUBLIC
                                  "${PROJECT_BINARY_DIR}"
                                  "${PROJECT_SOURCE_DIR}/MathFunctions"
                                  )
        ```

    -   可自定义库列表变量，将多个库作为list添加

        ````cmake
        # 将元素追加到list中, 变量类型为list与set变量不同
        # APPEND 表示添加 EXTRA_LIBS 为自定义lib名 后接库工程
        list(APPEND EXTRA_LIBS MathFunctions) 
        
        # lib include位置 同上
        list(APPEND EXTRA_INCLUDES  "${PROJECT_SOURCE_DIR}/MathFunctions")
        
        # 可利用自定义list添加
        add_executable(Tutorial main.cpp)
        target_link_libraries(Tutorial PUBLIC ${EXTRA_LIBS}) # link libray
        target_include_directories(Tutorial PUBLIC
                                    "${PROJECT_BINARY_DIR}" # 编译目录位置
                                    "${EXTRA_INCLUDES}"
                ) # 包含头文件路径
        ````


#### 4. 安装

1.  指明安装路径(若不指明则为默认)

    ```cmake
    SET(CMAKE_INSTALL_PREFIX "./")
    ```

2.  安装

    ```cmake
    # 安装可执行文件 
    # 前为TARGETS表示安装工程 只需指明可执行文件/lib名即可，无需路径
    # 后为DESTINATION表示安装在安装文件夹/bin下
    # 可在DESTINATION前添加
    # RUNTIME 表示可执行文件 bin
    # LIBRARY 表示动态库 lib
    # ARCHIVE 表示静态库 libstatic
    # 可执行文件一般安装在bin下
    INSTALL(TARGETS Tutorial DESTINATION bin)
    # 安装include头文件等文件
    # FILES提示表示文件地址
    # DESTINATION表示安装在安装文件夹/include下
    # 头文件一般安装在include下
    INSTALL(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
            DESTINATION include
            )
            
    # 安装库文件
    # TARGETS 表明安装的为库/执行文件 其应该为相应的lib名称
    # DESTINATION 表明安装路径为硬盘 后跟默认路径后的路径
INSTALL(TARGETS MathFunctions DESTINATION lib)
    # FILES 表明安装的为文件
    INSTALL(FILES MathFunctions.h DESTINATION include)
    
    # 安装文件夹
    INSTALL(DIRECTORY doc/ DESTINATION share/doc/)
    ```
    
    

​    

​    