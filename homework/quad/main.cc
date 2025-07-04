#include"../include/vector.h"
#include"../include/matrix.h"
#include"quad.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>

std::function<double(double)> func1 = [](double x) {return std::sqrt(x);};
std::function<double(double)> func2 = [](double x) {return 1.0/std::sqrt(x);};
std::function<double(double)> func3 = [](double x) {return std::sqrt(1.0 - x * x);};
std::function<double(double)> func4 = [](double x) {return std::log(x)/std::sqrt(x);};

std::function<double(double)> erfh1 = [](double x) {return std::exp(-x * x);};
std::function<double(double)> erfh2(double z) {
    std::function<double(double)> f = [=](double t) {
        return std::exp(-std::pow(z + (1 - t)/t, 2))/t/t;
    };
    return f;
};

double erf(double z, double acc, double eps) {
    if(z < 0 ) {return -erf(-z);}
    if(0 <= z && z <= 1) {return 2/std::sqrt(M_PI) * integrate(erfh1, 0, z, acc, eps);}
    return 1 - 2/std::sqrt(M_PI) * integrate(erfh2(z), 0, 1, acc, eps);
};

int main() {
    double res;
    double a, b, acc, eps;
    double analytic;

    //square root, func1
    a = 0.0, b = 1.0;
    acc = 1e-4, eps = 1e-4;
    res = integrate(func1, a, b, acc, eps);
    analytic = 2.0/3.0 * (std::pow(b, 3.0/2.0) - std::pow(a, 3.0/2.0));
    
    std::cout << "acc = " << acc << ", eps = " << eps << "\n";
    std::cout << "Integral of func1 : " << res << " expected to be : " << analytic << "\n"; 
    std::cout << "|implementation - analytic| <= acc =? " << (std::abs(res - analytic) <= acc) << "\n";
    std::cout << "|(implementation - analytic)/max(implementation, analytic)| <= eps =? " << (std::abs(res - analytic)/(std::max(std::abs(res), std::abs(analytic))) <= eps) << "\n";

    //inverse square root, func2
    res = integrate(func2, a, b, acc, eps);
    analytic = 2.0 * (std::sqrt(b) - std::sqrt(a)); 

    std::cout << "\n";
    std::cout << "Integral of func2 : " << res << " expected to be : " << analytic << "\n"; 
    std::cout << "|implementation - analytic| <= acc =? " << (std::abs(res - analytic) <= acc) << "\n";
    std::cout << "|(implementation - analytic)/max(implementation, analytic)| <= eps =? " << (std::abs(res - analytic)/(std::max(std::abs(res), std::abs(analytic))) <= eps) << "\n";

    //func3
    res = integrate(func3, a, b, acc, eps);
    analytic = M_PI / 4.0;      //checked with Wolfram

    std::cout << "\n";
    std::cout << "Integral of func3 : " << res << " expected to be : " << analytic << "\n"; 
    std::cout << "|implementation - analytic| <= acc =? " << (std::abs(res - analytic) <= acc) << "\n";
    std::cout << "|(implementation - analytic)/max(implementation, analytic)| <= eps =? " << (std::abs(res - analytic)/(std::max(std::abs(res), std::abs(analytic))) <= eps) << "\n";

    //func4
    res = integrate(func4, a, b, acc, eps);
    analytic = -4.0;

    std::cout << "\n";
    std::cout << "Integral of func4 : " << res << " expected to be : " << analytic << "\n"; 
    std::cout << "|implementation - analytic| <= acc =? " << (std::abs(res - analytic) <= acc) << "\n";
    std::cout << "|(implementation - analytic)/max(implementation, analytic)| <= eps =? " << (std::abs(res - analytic)/(std::max(std::abs(res), std::abs(analytic))) <= eps) << "\n";

    //erf
    double erf1 =  0.84270079294971486934;
    vector erfxs, erfys;
    vector xsAcc, ysAcc;
    
    for(double i = -3.5; i < 3.5; i += 1/8.0) {
        erfxs.push_back(i);
        erfys.push_back(erf(i, 1e-3, 1e-3));
    }

    for(int i = 0; i < 24; ++i) {
        xsAcc.push_back(std::pow(2, -i));
        ysAcc.push_back(std::abs(erf1 - erf(1, xsAcc[i], 0)));
    }
    
    std::cout << "\n\n";
    for(int i = 0; i < erfxs.size; ++i) std::cout << erfxs[i] << ", " << erfys[i] << "\n";

    std::cout << "\n\n";
    for(int i = 0; i < xsAcc.size; ++i) std::cout << xsAcc[i] << ", " << ysAcc[i] << "\n";

    return 0;
}