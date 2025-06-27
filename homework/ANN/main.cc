#include"ann.h"
#include<cmath>
#include<fstream>
#include<iostream>
#include<functional>

std::function<double(double)> fCosExp = [](double x) {
    return std::cos(5 * x - 1) * std::exp(-x * x);
};


int main() {
    std::cout << "--- Task A ---\n";

    int n = 45;
    vector xs(n), ys(n);
    xs = linspace(-1, 1, n);

    for(int i = 0; i < n; ++i) {
        ys[i] = fCosExp(xs[i]);
    }

    int hiddenNeurons = 8;
    std::cout << "Training network on " << hiddenNeurons << " hidden neurons over the interval -1 to 1 with "
              << n << " datapoints. Approximating function f(x) = cos(5*x-1)*exp(-x^2)\n";

    ann artificialNeuralNetwork(hiddenNeurons, "gaussian wavelet");
    artificialNeuralNetwork.train(xs, ys);

    std::cout << "Training ended\n";

    std::cout << "\n\n";
    std::cout << "#Training data\n";
    for(int i = 0; i < n; ++i) std::cout << xs[i] << " " << ys[i] << "\n";

    std::cout << "\n\n";
    std::cout << "#ANN response\n";
    for(int i = 0; i < n; ++i) {
        double x = xs[i];
        std::cout << x << " " << artificialNeuralNetwork.response(x) << "\n";
    }

    std::cout << "\n";
    std::cout << "--- Task B --- \n";
    std::cout << "\n\n";
    std::cout << "#ANN first derivative\n";
    for(int i = 0; i < n; ++i) {
        double x = xs[i];
        std::cout << x << " " << artificialNeuralNetwork.derivative(x) << "\n";
    }

    std::cout << "\n\n";
    std::cout << "#ANN second derivative\n";
    for(int i = 0; i < n; ++i) {
        double x = xs[i];
        std::cout << x << " " << artificialNeuralNetwork.secondDerivative(x) << "\n";
    }

    std::cout << "\n\n";
    std::cout << "#ANN integral\n";
    for(int i = 0; i < n; ++i) {
        double x = xs[i];
        std::cout << x << " " << artificialNeuralNetwork.integral(x) << "\n";
    }

    return 0;
}