#include"mcint.h"
#include<random>


vector plainmc(std::function<double(vector)>& f, vector a, vector b, int N) {
    int dim = a.size;
    double V = 1;

    std::default_random_engine randomEngine;
    std::vector<std::uniform_real_distribution<double>> uniformRealDistribution(dim);

    for(int i = 0; i < dim; ++i) {
        V *= b[i] - a[i];
        uniformRealDistribution[i] = std::uniform_real_distribution<double>(a[i], b[i]);
    }

    double sum1 = 0, sum2 = 0;
    vector x(dim);

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < dim; ++j) {
            double randomVal = uniformRealDistribution[j](randomEngine);
            x[j] = randomVal;
        }
        double fx = f(x);
        sum1 += fx;
        sum2 += fx * fx;
    }
    double mean = sum1/N, sigma = std::sqrt(sum2/N - mean * mean);
    vector result(2);
    result[0] = mean * V;
    result[1] = sigma * V/std::sqrt(N);
    return result;
}