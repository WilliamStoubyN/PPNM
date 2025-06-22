#include"../include/vector.h"
#include"../include/matrix.h"
#include"ode.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>

std::function<vector(double, vector)> harmonic = [](double x, const vector& y) {
    //y'' = -y
    vector deriv(2);
    deriv[0] = y[1];
    deriv[1] = -y[0];
    return deriv;
};

int main() {
    vector y0(2);
    double a, b;
    double acc, eps;
    vector xList;
    std::vector<vector> yList;

    //Debugging with harmonic example
    //y'' = -y
    y0[0] = 0.0; y0[1] = 1.0;
    a = 0.0, b = 15;
    acc = 0.001, eps = 0.001;
    auto harmonicStepper = rkDriver(harmonic, a, b, y0, 0.125, acc, eps);

    vector xListHarmonic = std::get<0>(harmonicStepper);
    std::vector<vector> yListHarmonic = std::get<1>(harmonicStepper);
    std::cout << "\n\n";
    for(int i = 0; i < xListHarmonic.size; ++i) std::cout << xListHarmonic[i] << ", " << yListHarmonic[i][0] << "\n";

    return 0;
}

