## Quadprogpp 使用
#### 1. Quadprogpp 简介  
***Quadprogpp*** 是由*Luca Di Gaspero*所写的
*c++* *QP*问题求解器, 其功能与*Matlab*中的二次规划*solver*一致。  

在QP问题中，其标准形式为:  
$$  
\begin{aligned}
    \underset{x}{min} &f = \frac{1}{2}x^TGx + g_0^Tx  \\
    s.t:& \\
    &CE^Tx + ce_0 = 0  \\
    &CI^Tx + ci_0 \geqslant 0  \\
\end{aligned}
$$
其中$G$为正定矩阵, 若求解问题约束形如下式  
$$
\begin{aligned}
    &A^Tx  = b  \\
    &C^Tx  \geqslant d  \\
\end{aligned}
$$
则对应标准形式有  
$$
\begin{aligned}
   & CE = A \\
   & CI = C \\
   & ce_0 = -b \\
   & ci_0 = -d \\
\end{aligned}
$$
由此构造***Quadprogpp***可用的*QP*问题形式。

#### 2. Quadprogpp 安装
[Install](https://github.com/liuq/QuadProgpp). 

#### 3. Quadprogpp 使用
- 初始化  
  在*Quadprogpp*中利用*cpp*标准库构造了两种模板类数据格式`quadprogpp::Matrix<T>`与`quadprogpp::Vector<T>`, 用户可由该模板类事先指定矩阵维数,也可构造动态矩阵不事先指定位数。两种构造方式如下所示。
  ```
    quadprogpp::Matrix<double> G; //构造动态矩阵
    G.resize(n, n); //后指定维数
  ```
  ```
    quadprogpp::Matrix<double>G(2,2); //事先指定
  ```
  
  
  *Notes：*在*Quadprogpp*中要求矩阵位数小于**20 * 20**，但也可以通过修改源码变量来修改这一限制。

- 求解器  
    ```
     f = solve_quadprog(G, g0, CE, ce0, CI, ci0, x)
    ```
    其中各个参数的定义如标准形式所示, $x$为优化变量,需要事先构造给定,同时在求解的过程中变量$G$会改变, 因此在求解够矩阵$G$与原构造矩阵不同。在求解的最后$Solver$会返回*double*类型的最优函数值。

#### 4. Cmakelists编写  
```
    include_directories(/usr/local/include/QuadProg++)

    add_executable(QuadProgpp_tuitor main.cpp)

    target_link_libraries(QuadProgpp_tuitor libquadprog.a)
```
在*Cmakelists*中需要引入*QuadProg++*头文件, 默认安装在`/usr/local/include/`下, 同时需要链接静态库`libquadprog.a`, 否则报错*未定义引用*。
  





