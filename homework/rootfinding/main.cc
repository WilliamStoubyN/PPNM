#include"../include/vector.h"
#include"../include/matrix.h"
#include"../ode/ode.h"
#include"rootfinder.h"
#include<cmath>
#include<functional>
#include<string>
#include<iostream>
#include<fstream>
#include<vector>

std::function<vector(vector)> func1 = [](vector x) {
    return 4 * x + 5;
};

std::function<vector(vector)> func2 = [](vector x) {
    return vector({x[0] * x[0], x[1] * x[1]});
};

std::function<double(vector)> rosenbrockValley = [](vector x) {
    return std::pow(1 - x[0], 2) + 100 * std::pow( x[1] - x[0] * x[0], 2);
};

std::function<vector(vector)> rosenbrockGradient = [](vector x) {
    vector gradient(2);
    gradient[0] = -2 * (x[0] - 1) - 400 * x[0] * (x[1] - x[0] * x[0]);
    gradient[1] = 200 * (x[1] - x[0] * x[0]);
    return gradient;
};

std::function<double(vector)> himmelblau = [](vector x) {
    return std::pow(x[0] * x[0] + x[1] - 11, 2) + std::pow(x[0] + x[1] * x[1] - 7, 2);
};

std::function<vector(vector)> himmelblauGradient = [](vector x) {
    vector gradient(2);
    gradient[0] = 4 * (x[0] * x[0] + x[1] - 11) * x[0] + 2 * (x[0] + x[1]*x[1] - 7);
    gradient[1] = 2 * (x[0] * x[0] + x[1] - 11) + 4 * (x[0] + x[1] * x[1] - 7) * x[1];
    return gradient;
};


int main() {
    vector a, root;
    double acc = 1e-5;

    std::cout << "--- Task A ---\n" 
              << "Test functions\n";
    
    std::cout << "Accuracy = " << acc << "\n";
    a = vector({10});
    root = newton(func1, a, acc);
    std::cout << "f(x) = 4x-5\n"
              << "Initial guess = " << a << "\n"
              << "Expected root = " << -1.25 << "\n"
              << "Found root = " << root << "\n\n";

    a  = vector({0.5, 0.5});
    root = newton(func2, a, acc);
    std::cout << "f(x) = x^2 + y^2\n"
              << "Initial guess = (" << a[0] << "," << a[1] << ")\n"
              << "Expected root = (0,0)\n"
              << "Found root = (" << root[0] << "," << root[1] << ")\n\n";


    a = vector({2.5, 2.5});
    root = newton(rosenbrockGradient, a, acc);
    std::cout << "Rosenbrock's Valley Function\n"
              << "Initial guess = (" << a[0] << "," << a[1] << ")\n"
              << "Expected min = (1,1)\n"
              << "Found root of gradient = (" << root[0] << "," << root[1] << ")\n\n";
    
    a = vector({4.0, 4.0});
    std::cout << "Himmelblau's function\n"
              << "Initial guess = (" 
              << a[0] << "," << a[1] << ") and ("
              << -a[0] << "," << a[1] << ") and ("
              << a[0] << "," << -a[1] << ") and ("
              << -a[0] << "," << -a[1] << ")\n"
              << "Expected min = (3, 2)\n"
              << "Expected min = (-2.80512, 3.13131)\n"
              << "Expected min = (3.58443, -1.84813)\n"
              << "Expected min = (-3.77931, -3.28329)\n";
    newton(himmelblauGradient, vector({2.5, 2.5}), acc).print("Found root = ");
    newton(himmelblauGradient, vector({-2.5, 2.5}), acc).print("Found root = ");
    newton(himmelblauGradient, vector({2.5, -2.5}), acc).print("Found root = ");
    newton(himmelblauGradient, vector({-2.5, -2.5}), acc).print("Found root = ");

    return 0;
}