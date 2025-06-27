#include"ann.h"

double ann::response(double x) const {
    double response = 0;
    for(int i = 0; i < n; ++i) response += fActivation((x - a[i]/b[i])) * w[i];
    return response;
}

void ann::train(const vector& x, const vector& y) {
    vector start = vector(n * 3);
    for(int i = 0; i < n; ++i) {
        start[i] = a[i];
        start[i + n] = b[i];
        start[i + 2 * n] = w[i];
    }

    //cost function
    std::function<double(vector)> fCost = [&](vector p) {
        for(int i = 0; i < n; ++i) {
            a[i] = p[i];
            b[i] = p[i + n];
            w[i] = p[i + 2 * n];
        }
        double costSum = 0.0;
        for(int i = 0; i < x.size; ++i) costSum += std::pow(response(x[i]) - y[i], 2);
        return costSum;
    };

    //minimize cost function
    vector pOpt = std::get<0>(newton(fCost, start, 1e-4));

    for(int i = 0; i < n; ++i) {
        a[i] = pOpt[i];
        b[i] = pOpt[i + n];
        w[i] = pOpt[i + 2 * n];
    }
}

double ann::derivative(double x) const {
    double derivative = 0;
    for(int i = 0; i < n; ++i) {
        double z = (x - a[i])/b[i];
        derivative += w[i]/b[i] * fActivationPrime(z);
    }
    return derivative;
}

double ann::secondDerivative(double x) const {
    double secondDerivative = 0;
    for(int i = 0; i < n; ++i) {
        double z = (x - a[i])/b[i];
        secondDerivative += w[i]/b[i]/b[i] *  fActivationPrimePrime(z);
    }
    return secondDerivative;
}

double ann::integral(double x) const {
    double integral = 0;
    for(int i = 0; i < n; ++i) {
        double z = (x - a[i])/b[i];
        integral += w[i] * b[i] * (fActivationIntegral(z) - 1.0/2.0 * std::exp(-a[i]*a[i]/b[i]/b[i]));
    }
    return integral;
}
