#include"spline.h"
#include"../homework/include/vector.h"
#include<iostream>
#include<cmath>
#include<string>

//TODO
//Define functions for plotting points instead of writing them repeatedly


int printCubicDebugData() {
    int N = 5000;
    vector xs(N), ys(N), yPrime(N);
    double xInit = 0;
    double xFin = 2*M_PI;
    xs = linspace(xInit, xFin, N);

    for(int i = 0; i < N; ++i) {
        // ys[i] = std::sin(xs[i]);
        // yPrime[i] = std::cos(xs[i]); 

        ys[i] = std::cos(xs[i]);
        yPrime[i] = -std::sin(xs[i]);

        // ys[i] = xs[i] * xs[i] * std::sin(1/xs[i]);
        // yPrime[i] = 2 * xs[i] * std::sin(1/xs[i]) - std::cos(1/xs[i]);

        // ys[i] = std::exp(xs[i]);
        // yPrime[i] = std::exp(xs[i]);

        // ys[i] = std::pow(xs[i], 3);
        // yPrime[i] = 3 * xs[i] * xs[i];
    }

    cubicSubSpline cubicSubSpline(xs, ys, yPrime);
    
    //Sampled points for plotting
    std::cout << "#Sampled points\n";
    for(int i = 0; i < xs.size; ++i) std::cout << xs[i] << " " << ys[i] << " " << yPrime[i] << "\n";

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
    //This is not guaranteed to produce a continious plot
    // std::cout << "\n\n";
    // std::cout << "#Spline double derivative points\n";
    // for(double i = xInit; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << cubicSubSpline.doubleDerivative(i) << "\n";

    return 0;
};

int printQuarticDebugData() {
    int N = 5000;
    vector xs(N), ys(N), yPrime(N);
    double xInit = 0;
    double xFin = 2*M_PI;
    xs = linspace(xInit, xFin, N);

    for(int i = 0; i < N; ++i) {
        // ys[i] = std::sin(xs[i]);
        // yPrime[i] = std::cos(xs[i]); 

        ys[i] = std::cos(xs[i]);
        yPrime[i] = -std::sin(xs[i]);

        // ys[i] = xs[i] * xs[i] * std::sin(1/xs[i]);
        // yPrime[i] = 2 * xs[i] * std::sin(1/xs[i]) - std::cos(1/xs[i]);

        // ys[i] = std::exp(xs[i]);
        // yPrime[i] = std::exp(xs[i]);

        // ys[i] = std::pow(xs[i], 3);
        // yPrime[i] = 3 * xs[i] * xs[i];
    }

    quarticSubSpline quarticSubSpline(xs, ys, yPrime);

    //Sampled points for plotting
    std::cout << "#Sampled points\n";
    for(int i = 0; i < xs.size; ++i) std::cout << xs[i] << " " << ys[i] << " " << yPrime[i] << "\n";

    //Quartic sub-spline points for plotting
    std::cout << "\n\n";
    std::cout << "#Spline points\n";
    for(double i = xInit; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << quarticSubSpline.evaluate(i) << "\n";

    //Quartic sub-spline derivative for plotting
    std::cout << "\n\n";
    std::cout << "#Spline derivative points\n";
    for(double i = xInit; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << quarticSubSpline.derivative(i) << "\n";

    //Quartic sub-spline double derivative
    //This is should be guaranteed to produce a continious plot
    std::cout << "\n\n";
    std::cout << "#Spline double derivative points\n";
    for(double i = xInit; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << quarticSubSpline.doubleDerivative(i) << "\n";

    return 0;
}

int main(int argc, char** argv) {
    int task = 0;

    for(int i = 0; i < argc; ++i) {
        std::string arg = argv[i];

        if(arg == "--task" && i + 1 < argc) task = std::stoi(argv[i + 1]);
    }


    if(task == 1) return printCubicDebugData();
    if(task == 2) return printQuarticDebugData();
    else return 0;

    return 0;
}