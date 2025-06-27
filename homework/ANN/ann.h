#ifndef HAVE_ANN_H
#define HAVE_ANN_H

#include"../include/vector.h"
#include"../include/matrix.h"
#include"../minimization/minimizer.h"
#include<cmath>
#include<functional>
#include<string>
#include<iostream>
#include<random>
#include<exception>

class ann {
    public:
        int n;                          //number of neurons
        vector px;                      //vector of weights
        vector a,b,w;                   //network parameters
        std::string activation;         //determines which activation function to use

        std::function<double(double)> fActivation, fActivationPrime, fActivationPrimePrime, fActivationIntegral;

        ann(int n, std::string activation) : n(n), a(n), b(n), w(n), activation(activation) {
            double start = -1.0, end = 1.0;
            for(int i = 0; i < n; ++i) {
                a[i] = start + i * ((end - start) / (n - 1.0));
                b[i] = 0.5;
                w[i] = 2;
            };

            if(activation == "gaussian wavelet") {
                fActivation = [](double x) {return x * std::exp(-x * x);};
                fActivationPrime = [](double x) {return (1 - 2 * x * x) * std::exp(-x * x);};
                fActivationPrimePrime = [](double x) {return 2 * x * (2 * x * x - 3) * std::exp(-x * x);};
                fActivationIntegral = [](double x) {return -1.0/2.0 * std::exp(-x * x);};
            } else if(activation == "gaussian") {
                fActivation = [](double x) {return std::exp(-x * x);};
                // dfActivation = [double x] {return -2 * x *  std::exp(-x * x);};
            } else if(activation == "wavelet") {
                fActivation = [](double x) {return std::cos(5 * x) * std::exp(-x * x);};
                // dfActivation = [double x] {return -std::exp(-x * x) * (std::cos(5 * x) * 2 * x + 5 * std::sin(5 * x));};
            } else {throw std::invalid_argument("Unknown activation function, choose from: 'gaussian wavelet', 'gaussian', 'wavelet'");};
        }

        ann() = default;                //default ctor
        ann(const ann&) = default;      //copy ctor
        ann(ann&&) = default;           //move ctor
        ~ann() = default;               //destructor
        ann& operator=(const ann&) = default;       //copy assignment
        ann& operator=(ann&&) = default;            //move assignment

        double response(double x) const;
        double derivative(double x) const;
        double secondDerivative(double x) const;
        double integral(double x) const;
        void train(const vector& x, const vector& y);
};


#endif