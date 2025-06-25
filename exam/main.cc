#include"spline.h"
#include"../homework/include/vector.h"
#include<iostream>
#include<cmath>
#include<string>

int printCubicDebugData() {
    int N = 5000;
    vector xs(N), ys(N), dydx(N);
    double xInit = 0;
    double xFin = 2*M_PI;
    xs = linspace(xInit, xFin, N);

    for(int i = 0; i < N; ++i) {
        // ys[i] = std::sin(xs[i]);
        // dydx[i] = std::cos(xs[i]); 

        ys[i] = std::cos(xs[i]);
        dydx[i] = -std::sin(xs[i]);

        // ys[i] = xs[i] * xs[i] * std::sin(1/xs[i]);
        // dydx[i] = 2 * xs[i] * std::sin(1/xs[i]) - std::cos(1/xs[i]);

        // ys[i] = std::exp(xs[i]);
        // dydx[i] = std::exp(xs[i]);

        // ys[i] = std::pow(xs[i], 3);
        // dydx[i] = 3 * xs[i] * xs[i];
    }

    cubicSubSpline cubicSubSpline(xs, ys, dydx);
    
    //Sampled points for plotting
    std::cout << "#Sampled points\n";
    for(int i = 0; i < xs.size; ++i) std::cout << xs[i] << " " << ys[i] << " " << dydx[i] << "\n";

    //Cubic sub-spline points for plotting
    std::cout << "\n\n";
    std::cout << "#Spline points\n";
    for(double i = xInit; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << cubicSubSpline.evaluate(i) << "\n";

    //Cubic sub-spline derivative for plotting
    std::cout << "\n\n";
    std::cout << "#Spline derivative points\n";
    for(double i = xInit; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << cubicSubSpline.derivative(i) << "\n";

    //Cubic sub-spline integral for plotting
    std::cout << "\n\n";
    std::cout << "#Spline integral points\n";
    for(double i = xInit; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << cubicSubSpline.integral(i) << "\n";
    std::cout << "#Spline integral value = " << cubicSubSpline.integral(xFin) << "\n";

    //Cubic sub-spline double derivative
    //This should produce a discontinious function
    // std::cout << "\n\n";
    // std::cout << "#Spline double derivative points\n";
    // for(double i = xInit; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << cubicSubSpline.doubleDerivative(i) << "\n";

    return 0;
};



int main(int argc, char** argv) {
    int task = 0;

    for(int i = 0; i < argc; ++i) {
        std::string arg = argv[i];

        if(arg == "--task" && i + 1 < argc) task = std::stoi(argv[i + 1]);
    }


    if(task == 1) return printCubicDebugData();
    else return 0;

    return 0;
}