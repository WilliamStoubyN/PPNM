#include"spline.h"
#include"../homework/include/vector.h"
#include<iostream>
#include<cmath>
#include<string>

int printDebuggingData() {
    int N = 15;
    vector xs(N), ys(N), dydx(N);

    for(int i = 0; i < N; ++i) {
        xs[i] = 15.0/N * i;
        ys[i] = std::sin(xs[i]);
        dydx[i] = std::cos(xs[i]); 
    }

    cubicSubSpline cubicSpline(xs, ys, dydx);
    
    //Sampled points
    std::cout << "#Sampled points\n";
    for(int i = 0; i < xs.size; ++i) std::cout << xs[i] << " " << ys[i] << " " << dydx[i] << "\n";

    //Spline points
    std::cout << "\n\n";
    std::cout << "#Spline points\n";
    for(double i = 0; i <= N - 1; i += 1/8.0) std::cout << i << " " << cubicSpline.evaluate(i) << "\n";

    return 0;
};

int main(int argc, char** argv) {
    int task = 0;

    for(int i = 0; i < argc; ++i) {
        std::string arg = argv[i];

        if(arg == "--task" && i + 1 < argc) task = std::stoi(argv[i + 1]);
    }


    if(task == 1) return printDebuggingData();
    else return 0;

    return 0;
}