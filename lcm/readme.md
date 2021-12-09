## lcm使用  
#### 0. 文件架构    
- type: 自定义数据类型  
  - example_t.lcm 自定义数据  
  - gen_type.sh 生成可用文件指令    
  - exlcm  可用文件  
- src： cpp文件  
- script： python文件  

#### 1. 自定义数据类型  
- example_t.lcm： 自定义数据类型  
```
    package exlcm; // 定义数据类型名称， 数据类名与namespace  

    // 数据定义， 为结构体类型  
    struct example_t
    {
        int64_t timestamp;
        double position[3];
        double orientation[4];
        int32_t num_ranges;
        int16_t ranges[num_ranges];
        string name;
        boolean enabled;
    }
```  
在数据类型定义中首先定义*package*名称， 由于在实际的生成数据中*lcm*讲*xx.lcm*生成为类，所以该名称用于  
    1. 生成数据时的文件夹名   
    2. 生成数据的namespace  
后定义*struct*名称，用于class名称与数据名称  
- gen_type.sh 生成可用文件指令    
    其中包含   
```
    lcm-gen -x example_t.lcm    # cpp 生成cpp可用数据  
    lcm-gen -p example_t.lcm    # py 生成python可用数据  
```   
其他语言生成指令详见[LCM](https://lcm-proj.github.io/tut_lcmgen.html).  
- exlcm  可用文件  
以类的形式定义数据，便于引用. 其中cpp类型仅包含hpp文件.  

#### 2. cpp  
``` 
    #include<lcm/lcm-cpp.hpp>  
    #include"exlcm/example_t.hpp"  
```  
添加引用, 其中`<lcm/lcm-cpp.hpp>`为lcm cpp封装，`"exlcm/example_t.hpp`为用户自定义数据, 在引用时使用相对*CmakeLists*设置的相对路径, 
详细在*CmakeLists*中解释.  
  
数据填充部分与*ROS*相似, 安装对应数据类型格式填充即可.  


```
    lcm.publish("EXAMPLE", &my_data);
```  
发送时第一个参数为*topic name*, 用于发送与接收的标识, 第二位参数为数据.  


在接收时需要定义处理class, 并在class中定义接收处理函数  
```
    void handleMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan,  const exlcm::example_t* msg)
``` 
`const std::string& chan`为*topic name*, `const exlcm::example_t* msg`为常指针类型的接收数据格式.  
  
```
    lcm.subscribe("EXAMPLE", &Handle::handleMessage, &handlerObject);
```  
接收时第一个参数为*topic name*, 第二个参数为自定义类::处理函数, 第三个参数为自定义类的实例化.  

```
    lcm.handle()
```  
为阻塞函数,类似于`ros::spinOnce()`, 当需要处理时跳至处理函数, 无详细接收时阻塞等待. 若不想阻塞等待可以用其他函数, 详见python  


*Notes：CMakeLists的编写*  
无需对数据进行*install*，按照库引用链接即可.  
```
    cmake_minimum_required(VERSION 3.10)  
    project(LCM)  

    set(CMAKE_CXX_STANDARD 11)  
    find_package(lcm)               # 引入lcm pkg  
    include_directories("../type")  # 引入用户自定义数据类型  

    add_executable(LCM_Client send_msg.cpp)     # 分别链接发送与接收程序, 不可链接为同一工程.  
    target_link_libraries(LCM_Client lcm)  

    add_executable(LCM_Server listener.cpp)  
    target_link_libraries(LCM_Server lcm)  
```  
在引入用户自定义数据时可利用`include_directories("../type")`将自定义数据hpp所在的文件夹包含, 在cpp程序中已该包含路径为起点引入hpp文件.  

#### 3. python  
```
    import lcm  # 引入lcm
    from type.exlcm import example_t # 按照相对路径引入数据  
```
*type.exlcm*代表*type*文件夹间下的*exlcm*文件夹.  

```
    lc.publish("EXAMPLE", msg.encode())  
    msg = example_t.decode(data)
```  
再发送时利用*encode*编码发送, 接收时利用*decode*解码接收.  
```
    while True:  
        rfds, wfds, efds = select.select([lc.fileno()], [], [], timeout)  
        if rfds:  
            lc.handle()  
        else:  
            print("Waiting for message...")  
```  
若不想阻塞等待, 可利用`lc.fileno()`字符判断是否处理接收.  










