#include"spline.h"
#include"../include/vector.h"
#include<iostream>
#include<cmath>

int main(int argc, char** argv) {
    std::string p = "";

    for(int i = 0; i < argc; ++i) {
        std::string arg = argv[i];

        if(arg == "-p" && i + 1<argc) p = argv[i + 1];
    }

    int n = 14;
    vector xs(n),
           ys(n);

    for(int i = 0; i < n; ++i) {
        xs[i] = 14.0/n * i;
        ys[i] = std::cos(xs[i]);
    }

    std::cout << "--- Task A ---\n";
    std::cout << "Linear spline \n";
    std::cout << "Integral of linear spline of cos(x) from 0 to 2pi : " << linterpInteg(xs, ys, 2 * M_PI) << " is expected to be approx 0\n";
    std::cout << "Integral of linear spline of cos(x) from 0 to 13 : " << linterpInteg(xs, ys, 13) << "\n";

    //Sampled points
    std::cout << "\n\n";
    std::cout << "#Sampled points\n";
    for(int i = 0; i < n; ++i) std::cout << xs[i] << " " << linterp(xs, ys, i) << "\n";

    //Linear spline points
    std::cout << "\n\n";
    std::cout << "#Linear spline points\n";
    for(double i = 0; i <= 13; i += 1/12.0) std::cout << i << " " << linterp(xs, ys, i) << "\n";

    //Linear spline antiderivative
    std::cout << "\n\n";
    std::cout << "#Linear spline integral\n";
    for(double i = 0; i <= 13; i += 1/12.0) std::cout << i << " " << linterpInteg(xs, ys, i) << "\n";

    std::cout << "\n";
    std::cout << "--- Task B ---\n";
    std::cout << "Quadratic spline\n";

    int N = 10;
    vector xs2(N);
    vector ys1(N), ys2(N), ys3(N), ysPlot(N);
    for(int i = 0; i < N; ++i) {
        xs2[i] = 10.0/N * i;
        ys1[i] = 1;
        ys2[i] = i;
        ys3[i] = i*i;
        ysPlot[i] = std::cos(xs2[i]);
    }
    quadraticSpline qSpline1(xs2, ys1);
    std::cout << "Coefficients for constant function:\n";
    qSpline1.b.print("b = ");
    qSpline1.c.print("c = ");
    std::cout << "Expected b[i] = 0, c[i] = 0 for all i\n";

    std::cout << "\n";
    quadraticSpline qSpline2(xs2, ys2);
    std::cout << "Coefficients for linear function:\n";
    qSpline2.b.print("b = ");
    qSpline2.c.print("c = ");
    std::cout << "Expected b[i] = 1, c[i] = 0 for all i\n";

    std::cout << "\n";
    quadraticSpline qSpline3(xs2, ys3);
    std::cout << "Coefficients for quadratic function:\n";
    qSpline3.b.print("b = ");
    qSpline3.c.print("c = ");
    std::cout << "Expected b[1,1,5,5,9,9,...] = 0, c[i] = [0,2,0,2,...] for all i\n";

    std::cout << "\n\n";
    std::cout << "#Sampled points from sin(x)";
    for(int i = 0; i < N; ++i) std::cout << xs2[i] << " " << ysPlot[i] << "\n";

    std::cout << "\n\n";
    std::cout << "#Spline points from sin(x)";
    quadraticSpline qSplinePlot(xs2, ysPlot);
    for(double i = 0; i <= 9.0; i += 1/8.0) std::cout << i << " " << qSplinePlot.evaluate(i) << "\n";

    std::cout << "\n\n";
    std::cout << "#Spline derivative points from sin(x)";
    for(double i = 0; i <= 9.0; i += 1/8.0) std::cout << i << " " << qSplinePlot.derivative(i) << "\n";

    std::cout << "\n\n";
    std::cout << "#Spline integral points from sin(x)";
    for(double i = 0; i <= 9.0; i += 1/8.0) std::cout << i << " " << qSplinePlot.integral(i) << "\n";

    return 0;
}