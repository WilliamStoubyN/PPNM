#include"spline.h"
#include"../homework/include/vector.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>


void task0() {
    std::cout << "=============== Project 17 ===============\n"
              << "Cubic sub-spline for data with derivatives\n"
              << "URL: http://212.27.24.106:8080/prog/projex/spline-with-yprime.htm\n"
              << "Backup URL: https://fedorov.sdfeu.org/prog/projex/spline-with-yprime.htm\n"
              << "Exam Number: 211014\n"
              << "Date: 27-06-2025\n\n";

    std::cout << "=============== Output ===============\n";
    //TODO
    //Tests of cubicSubSpline.integral()
    //Write description of S'' for cubic sub-spline and quartic sub-spline

};

void plotCubic() {
    int N = 100;
    vector xs(N), ys(N), yPrime(N);
    double xInit = 0;
    double xFin = 2*M_PI;
    xs = linspace(xInit, xFin, N);

    for(int i = 0; i < N; ++i) {
        ys[i] = std::sin(xs[i]);
        yPrime[i] = std::cos(xs[i]); 

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
    std::cout << "\n\n";
    std::cout << "#Spline double derivative points\n";
    for(double i = xInit; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << cubicSubSpline.doubleDerivative(i) << "\n";
};

void plotQuartic() {
    int N = 100;
    vector xs(N), ys(N), yPrime(N);
    double xInit = 0;
    double xFin = 2*M_PI;
    xs = linspace(xInit, xFin, N);

    for(int i = 0; i < N; ++i) {
        ys[i] = std::sin(xs[i]);
        yPrime[i] = std::cos(xs[i]); 

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
    //This should be guaranteed to produce a continious plot
    std::cout << "\n\n";
    std::cout << "#Spline double derivative points\n";
    for(double i = xInit; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << quarticSubSpline.doubleDerivative(i) << "\n";
};

int main(int argc, char** argv) {
    int task = 0;

    for(int i = 0; i < argc; ++i) {
        std::string arg = argv[i];

        if(arg == "--task" && i + 1 < argc) task = std::stoi(argv[i + 1]);
    }

    if(task == 0) task0();
    if(task == 1) plotCubic();
    if(task == 2) plotQuartic();

    return 0;
}