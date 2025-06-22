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

std::function<vector(double, vector)> dampedHarmonic = [](double x, const vector& y) {
    vector deriv(2);
    deriv[0] = y[1];
    deriv[1] = -0.25 * y[1] - 5.0 * std::sin(y[0]);
    return deriv;
};

int main() {
    vector y0(2);
    double a, b;
    double acc, eps;
    vector xList;

    //Debugging with harmonic example
    //y'' = -y
    y0[0] = 1.0; y0[1] = 0;
    a = 0.0, b = 15.0;
    acc = 0.001, eps = 0.001;
    auto harmonicStepper = rkDriver(harmonic, a, b, y0, 0.125, acc, eps);
    vector xListHarmonic = std::get<0>(harmonicStepper);
    std::vector<vector> yListHarmonic = std::get<1>(harmonicStepper);
    
    std::cout << "\n\n";
    for(int i = 0; i < xListHarmonic.size; ++i) std::cout << xListHarmonic[i] << ", " << yListHarmonic[i][0] << "\n";

    //Damped harmonic (scipy odeint example)
    y0[0] = M_PI - 0.1, y0[1] = 0.0;
    a = 0.0, b = 10.0;
    acc = 0.001, eps = 0.001;
    auto dampedHarmonicStepper = rkDriver(dampedHarmonic, a, b, y0, 0.125, acc, eps);
    vector xListDampedHarmonic = std::get<0>(dampedHarmonicStepper);
    std::vector<vector> yListDampedHarmonic = std::get<1>(dampedHarmonicStepper);

    std::cout << "\n\n";
    for(int i = 0; i < xListDampedHarmonic.size; ++i) std::cout << xListDampedHarmonic[i] << ", " << yListDampedHarmonic[i][0] << "\n";
    
    std::cout << "\n\n";
    for(int i = 0; i < xListDampedHarmonic.size; ++i) std::cout << xListDampedHarmonic[i] << ", " << yListDampedHarmonic[i][1] << "\n";

    return 0;
}

