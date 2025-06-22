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

    return 0;
}