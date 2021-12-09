#include <iostream>
#include <Eigen/Core>
#include <QuadProg++/QuadProg++.hh>
#include <QuadProg++/Array.hh>

using namespace std;

int main() {
    Eigen::Matrix2d dyn_G;
    Eigen::Vector2d dyn_g0, dyn_CE;
    Eigen::Vector3d dyn_ci;
    Eigen::Matrix<double, 2, 3> dyn_CI;

    dyn_G << 4.0, -2.0, -2.0, 4.0;
    dyn_g0 << 6.0, 0.0;
    dyn_CE << 1.0, 1.0;
    dyn_CI << 1.0, 0.0, 1.0, 0.0, 0.0, 1.0;
    dyn_ci << 0.0, 0.0, -2.0;

    quadprogpp::Matrix<double> G, CE, CI;
    quadprogpp::Vector<double> g0, ce0, ci0, x;

    G.resize(2, 2);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            G[i][j] = dyn_G(i, j);
        }
    }

    g0.resize(2);
    for (int i = 0; i < 2; ++i) {
        g0[i] = dyn_g0(i);
    }

    CE.resize(2, 1);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 1; ++j) {
            CE[i][j] = dyn_CE(i, j);
        }
    }

    ce0.resize(1);
    ce0[0] = -3.0;

    CI.resize(2, 3);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            CI[i][j] = dyn_CI(i, j);
        }
    }

    ci0.resize(3);
    for (int i = 0; i < 3; ++i) {
        ci0[i] = dyn_ci(i);
    }
    std::cout<<"ci0: "<<ci0<<std::endl;
    x.resize(2);

    double f;
    f = quadprogpp::solve_quadprog(G, g0, CE, ce0, CI, ci0, x);
    std::cout<<"f: "<<f<<std::endl;
    std::cout<<"x: "<<x<<std::endl;

    clock_t startTime, endTime;
    startTime = clock();
    for (int i = 0; i < 1000; i++) {
        quadprogpp::solve_quadprog(G, g0, CE, ce0, CI, ci0, x);
    }
    endTime = clock();
    double total_time = (double)(endTime - startTime);
    total_time = total_time * 1000.0/ CLOCKS_PER_SEC;
    cout << total_time  << "ms" << endl;

    return 0;
}
