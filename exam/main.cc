#include"spline.h"
#include"../homework/include/vector.h"
#include<iostream>
#include<cmath>
#include<string>


//Output for Out.txt
void task0() {
    std::cout << "=============== Project 17 ===============\n"
              << "Cubic sub-spline for data with derivatives\n"
              << "URL: http://212.27.24.106:8080/prog/projex/spline-with-yprime.htm\n"
              << "Backup URL: https://fedorov.sdfeu.org/prog/projex/spline-with-yprime.htm\n"
              << "Exam Number: 211014\n"
              << "Date: 27-06-2025\n\n";

    std::cout << "=============== Output ===============\n";
    int N = 5000;
    vector xs(N), ys(N), yPrime(N);
    double xInitial = 0;
    double xFinal = 2*M_PI;
    xs = linspace(xInitial, xFinal, N);

    std::cout << "--- Extra Task 1 ---\n";  
    std::cout << "Testing that the cubic sub-spline integrate routine works as intended\n"
              << "using sin(x), x^3 and exp(x) from 0 to 2pi with N = " << N << " sample points\n"
              << "and that the first derivative of the sub-spline is equal to a given tabulated point:\n";
    

    for(int i = 0; i < N; ++i) {        //could have refactored this, but I'd rather make some finishing touches to some of the homework
        ys[i] = std::sin(xs[i]);
        yPrime[i] = std::cos(xs[i]); 
    }
    cubicSubSpline sinSpline(xs, ys, yPrime);
    std::cout << " - integral of spline using sin(x) from 0 to 2pi = " << sinSpline.integral(xFinal) << ", expected = 0" << "\n";
    std::cout << " - b[0] = yPrime[0] ? : " << approx(sinSpline.derivative(xs[0]), yPrime[0]) << "\n";
    std::cout << " - b[N/2] = yPrime[N/2] ? : " << approx(sinSpline.derivative(xs[N/2]), yPrime[N/2]) << "\n";
    std::cout << " - b[N-2] = yPrime[N-2] ? : " << approx(sinSpline.derivative(xs[N - 2]), yPrime[N - 2]) << "\n\n";

    for(int i = 0; i < N; ++i) {        
        ys[i] = xs[i] * xs[i] * xs[i];
        yPrime[i] = 2 * xs[i] * xs[i]; 
    }
    cubicSubSpline powSpline(xs, ys, yPrime);
    std::cout << " - integral of spline using x^3 from 0 to 2pi = " << powSpline.integral(xFinal) << ", expected ≈ 389.64" << "\n";
    std::cout << " - b[0] = yPrime[0] ? : " << approx(powSpline.derivative(xs[0]), yPrime[0]) << "\n";
    std::cout << " - b[N/2] = yPrime[N/2] ? : " << approx(powSpline.derivative(xs[N/2]), yPrime[N/2]) << "\n";
    std::cout << " - b[N-2] = yPrime[N-2] ? : " << approx(powSpline.derivative(xs[N - 2]), yPrime[N - 2]) << "\n\n";

    for(int i = 0; i < N; ++i) {        
        ys[i] = std::exp(xs[i]);
        yPrime[i] = std::exp(xs[i]); 
    }
    cubicSubSpline expSpline(xs, ys, yPrime);
    std::cout << " - integral of spline using e^x from 0 to 2pi = " << expSpline.integral(xFinal) << ", expected ≈ 534.49" << "\n";
    std::cout << " - b[0] = yPrime[0] ? : " << approx(expSpline.derivative(xs[0]), yPrime[0]) << "\n";
    std::cout << " - b[N/2] = yPrime[N/2] ? : " << approx(expSpline.derivative(xs[N/2]), yPrime[N/2]) << "\n";
    std::cout << " - b[N-2] = yPrime[N-2] ? : " << approx(expSpline.derivative(xs[N - 2]), yPrime[N - 2]) << "\n\n";

    std::cout << "--- Extra Task 2 ---\n";  
    std::cout << "The cubic sub-spline of sin(x) from 0 to 2pi can be seen together with its derivative,\n"
              << "integral and second derivative in 'plot/plot.cubicSubSpline.svg', alongside the\n" 
              << "sampled points themselves. One can clearly see a discontinuity in the second\n"
              << "derivative at around (x = 4).\n\n";

    std::cout << "The quartic sub-spline of sin(x) from 0 to 2pi can be seen together with its derivative,\n"
              << "and second derivative in 'plot/plot.quarticSubSpline.svg, alongside the sampled points.\n"
              << "Here, there is no clear discontinuity.\n";

};


//Output for out.cubicData.txt
void plotCubic() {
    int N = 100;
    vector xs(N), ys(N), yPrime(N);
    double xInitial = 0;
    double xFinal = 2*M_PI;
    xs = linspace(xInitial, xFinal, N);

    for(int i = 0; i < N; ++i) {
        ys[i] = std::sin(xs[i]);
        yPrime[i] = std::cos(xs[i]); 
    }

    cubicSubSpline cubicSubSpline(xs, ys, yPrime);
    
    //Sampled points for plotting
    std::cout << "#Sampled points\n";
    for(int i = 0; i < xs.size; ++i) std::cout << xs[i] << " " << ys[i] << " " << yPrime[i] << "\n";

    //Cubic sub-spline points for plotting
    std::cout << "\n\n";
    std::cout << "#Spline points\n";
    for(double i = xInitial; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << cubicSubSpline.evaluate(i) << "\n";

    //Cubic sub-spline derivative for plotting
    std::cout << "\n\n";
    std::cout << "#Spline derivative points\n";
    for(double i = xInitial; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << cubicSubSpline.derivative(i) << "\n";

    //Cubic sub-spline integral for plotting and testing
    std::cout << "\n\n";
    std::cout << "#Spline integral points\n";
    for(double i = xInitial; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << cubicSubSpline.integral(i) << "\n";
    std::cout << "#Spline integral value = " << cubicSubSpline.integral(xFinal) << "\n";

    //Cubic sub-spline second derivative
    //This is not guaranteed to produce a continious plot
    std::cout << "\n\n";
    std::cout << "#Spline second derivative points\n";
    for(double i = xInitial; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << cubicSubSpline.secondDerivative(i) << "\n";
};


//Output for out.quarticData.txt
void plotQuartic() {
    int N = 100;
    vector xs(N), ys(N), yPrime(N);
    double xInitial = 0;
    double xFinal = 2*M_PI;
    xs = linspace(xInitial, xFinal, N);

    for(int i = 0; i < N; ++i) {
        ys[i] = std::sin(xs[i]);
        yPrime[i] = std::cos(xs[i]); 
    }

    quarticSubSpline quarticSubSpline(xs, ys, yPrime);

    //Sampled points for plotting
    std::cout << "#Sampled points\n";
    for(int i = 0; i < xs.size; ++i) std::cout << xs[i] << " " << ys[i] << " " << yPrime[i] << "\n";

    //Quartic sub-spline points for plotting
    std::cout << "\n\n";
    std::cout << "#Spline points\n";
    for(double i = xInitial; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << quarticSubSpline.evaluate(i) << "\n";

    //Quartic sub-spline derivative for plotting
    std::cout << "\n\n";
    std::cout << "#Spline derivative points\n";
    for(double i = xInitial; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << quarticSubSpline.derivative(i) << "\n";

    //Quartic sub-spline second derivative
    //This should be guaranteed to produce a continious plot
    std::cout << "\n\n";
    std::cout << "#Spline second derivative points\n";
    for(double i = xInitial; i <= xs[xs.size - 1]; i += 1/8.0) std::cout << i << " " << quarticSubSpline.secondDerivative(i) << "\n";
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