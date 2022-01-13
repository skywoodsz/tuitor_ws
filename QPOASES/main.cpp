#include <iostream>
#include <qpOASES.hpp>
int main() {
    USING_NAMESPACE_QPOASES
    // 1. 构建QP问题
    QProblem example(2, 1); // 优化变量, 约束变量 维度

    // 2. 初始化第一个QP
    real_t H[2*2] = {1.0, 0.0, 0.0, 0.5}; // Hessian Matrix
    real_t A[1*2] = {1.0, 1.0};                    // 不等式/等式约束系数矩阵
    real_t g[2] = {1.5, 1.0};                      // 线性项系数 与maatlab不同为 x' * g
    real_t lb[2] = {0.5, -2.0};                    // x 下界
    real_t ub[2] = {5.0, 2.0};                     // x 上界
    real_t lbA[1] = {-1.0};                             // 不等式/等式上界 上下界相等时为等式约束
    real_t ubA[1] = {2.0};                              // 不等式/等式下界

    // 初始化第二个QP(MPC) 假设 H A不变
    real_t g_new[2] = {1.0, 1.5};
    real_t lb_new[2] = {0.0, -1.0};
    real_t ub_new[2] = {5.0, -0.5};
    real_t lbA_new[1] = {-2.0};
    real_t ubA_new[1] = {1.0};

    // 3. 求解
    Options options;
    example.setOptions(options);

    int nWSR = 10;                                           // 最大迭代次数
    example.init(H, g, A, lb, ub, lbA, ubA, nWSR);

    // 4. 得到最优解
    real_t xOpt[2];
    real_t yOpt[2+1];
    example.getPrimalSolution(xOpt);
    example.getDualSolution(yOpt);
    std::cout<<"PrimalSolution: "<<xOpt[0]<<","<<xOpt[1]<<std::endl;
    std::cout<<"DualSolution: "<<yOpt[0]<<","<<yOpt[1]<<yOpt[2]<<","<<std::endl;
    std::cout<<"ObjVal: "<<example.getObjVal()<<std::endl;

    //解第二个QP问题
    nWSR = 10;
    example.hotstart(g_new, lb_new, ub_new, lbA_new, ubA_new, nWSR);
    example.getPrimalSolution(xOpt);
    example.getDualSolution(yOpt);
    std::cout<<"PrimalSolution: "<<xOpt[0]<<","<<xOpt[1]<<std::endl;
    std::cout<<"DualSolution: "<<yOpt[0]<<","<<yOpt[1]<<yOpt[2]<<","<<std::endl;
    std::cout<<"ObjVal: "<<example.getObjVal()<<std::endl;

    example.printOptions();



    return 0;
}
