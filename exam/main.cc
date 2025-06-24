#include"spline.h"
#include"../homework/include/vector.h"
#include<iostream>
#include<cmath>

int main(int argc, char** argv) {
    int n = 0;

    for(int i = 0; i < argc; ++i) {
        std::string arg = argv[i];

        if(arg == "-n" && i + 1 < argc) n = std::stoi(argv[i + 1]);
    }

    int N = 15;
    vector xs(N), ys(N), dydx(N);

    for(int i = 0; i < N; ++i) {
        xs[i] = 15.0/N * i;
        ys[i] = std::sin(xs[i]);
        dydx[i] = std::cos(xs[i]); 
    }

    std::cout << "Test";




    return 0;
}