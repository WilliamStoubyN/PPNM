#include"minimizer.h"
#include"../include/vector.h"
#include"../include/matrix.h"
#include<iostream>
#include<cmath>
#include<functional>
#include<string>

std::function<double(vector)> rosenbrockValley = [](vector x) {
    return std::pow(1 - x[0], 2) + 100 * std::pow( x[1] - x[0] * x[0], 2);
};

std::function<double(vector)> himmelblau = [](vector x) {
    return std::pow(x[0] * x[0] + x[1] - 11, 2) + std::pow(x[0] + x[1] * x[1] - 7, 2);
};

int main() {
    double acc = 1e-6;

    //Rosenbrock's valley function
    vector xInit = vector({10,10});
    auto res = newton(rosenbrockValley, xInit, acc);
    vector xMinimum = std::get<0>(res);
    int iterations = std::get<1>(res);

    std::cout << "Rosenbrock's valley function\n";
    std::cout << "Implementation found a minimum at : (" << xMinimum[0] << "," << xMinimum[1] << ") after " << iterations << " iterations, expected minimum at : (1.0,1.0)"; //From Wikipedia: It has a global minimum at (x,y) = (a,a^2)

    //Himmelblau's function
    res = newton(himmelblau, xInit, acc);
    xMinimum = std::get<0>(res);
    iterations = std::get<1>(res);

    std::cout << "\n\n";
    std::cout << "Himmelblau's function\n";
    std::cout << "Implementation found a minimum at : (" << xMinimum[0] << "," << xMinimum[1] << ") after " << iterations << " iterations, expected minimum at : (3.0,2.0)"; //From Wikipedia: It has a local minimum at f(3.0, 2.0), which is identical to 3 other minima listed on Wikipedia

    return 0;
}