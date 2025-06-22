#include"lsfit.h"
#include"../include/matrix.h"
#include"../include/vector.h"
#include<iostream>
#include<vector>
#include<functional>
#include<cmath>

int main() {
    vector t = {1, 2, 3, 4, 6, 9, 10, 13, 15},
           y = {117, 100, 88, 72, 53, 29.5, 25.2, 15.2, 11.1},
           dy = {6, 5, 4, 4, 4, 3, 3, 2, 2};

    vector lny(y.size), 
           lndy(y.size);

    //ln(y) = ln(a) - λt
    std::vector<std::function<double(double)>> f = {
        [](double t) {return 1.0;},
        [](double t) {return -t;}
    };
    
    //δln(y) = dy/y follows from the Law of Accumulation, δln(y) = (dln(y)/dy) * dy = dy/y
    for(int i = 0; i < (int)y.size; ++i) {
        lny[i] = std::log(y[i]);
        lndy[i] = dy[i]/y[i];
    }

    auto fit = lsfit(f, t, lny, lndy);
    vector parameters = std::get<0>(fit);
    matrix covarianceMatrix = std::get<1>(fit);

    std::cout << "#Rutherford and Soddy results: \n";
    for(int i = 0; i < (int)t.size; ++i) std::cout << t[i] << " " << y[i] << " " << dy[i] << "\n";
    std::cout << "\n";

    std::cout << "Optimal parameters (a, λ):\n";
    parameters.print("parameters = ");
    covarianceMatrix.print("covariance matrix = ");
    std::cout << "parameter errors : " << std::sqrt(covarianceMatrix(0,0)) << ", " << std::sqrt(covarianceMatrix(1,1)) << "\n\n";
    double halfLife = std::log(2)/parameters[1];

    //From the Law of Accumulation we have
    double halfLifeError = std::log(2)/parameters[1]/parameters[1] * std::sqrt(covarianceMatrix(1,1));

    std::cout << "ThX has measured half-life : " << halfLife << " +/- " << halfLifeError << " days\n";
    std::cout << "224Ra has half-life : 3.6319 days" << "\n";
    std::cout << "The percentage deviation is : " << (halfLife - 3.6319)/3.6319 * 100 << "%\n";
    std::cout << "Experimental data is " << (halfLife - 3.6319)/halfLifeError << " standard deviations away from the modern measurement\n";

    return 0;
}