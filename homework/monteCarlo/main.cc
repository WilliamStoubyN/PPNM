#include"mcint.h"
#include"../include/vector.h"
#include<random>
#include<iostream>
#include<cmath>
#include<functional>
#include<string>

std::function<double(vector)> fUnitCircle = [](vector x) {
    if(x.norm() <= 1.0) return 1.0;
    else return 0.0;
};

std::function<double(vector)> fConstant = [](vector x) {
    return 1.0;
};

std::function<double(vector)> fCosines = [](vector x) {
    if(0 <= x[0] && x[0] <= M_PI && 
       0 <= x[1] && x[1] <= M_PI &&
       0 <= x[2] && x[2] <= M_PI) {
        return std::pow(M_PI, -3) * 1/(1 - std::cos(x[0]) * std::cos(x[1]) * std::cos(x[2]));
       }
    return 0.0;
};

std::string resultToString(const vector result, double analytic, int N) {
    double integralVal = result[0],
           error = result[1];
    std::string s = "MC calculated = " + std::to_string(integralVal) + " +/- " + std::to_string(error) + ", expected = " + std::to_string(analytic) + "\nwith " + std::to_string(N) + " sample points \n" + "|MC - analytic| = " + std::to_string(std::abs(analytic - integralVal)) + "\n";
    return s;
};

int main() {
    vector a, b, result;
    int N;
    double analytic;

    //Unit circle
    a = vector({-1, -1});
    b = vector({1, 1});
    N = 100000;
    result = plainmc(fUnitCircle, a, b, N);
    analytic = M_PI;

    std::cout << "--- Task A ---\n";
    std::cout << "Unit Circle\n";
    std::cout << resultToString(result, analytic, N);

    
    std::cout << "\n\n";
    std::cout << "#Data to plot estimated- and actual error as functions of N\n";

    //I know it's ugly but it works
    vector Ns, estErrors, actErrors;
    for(int i = 0; i < 18; ++i) {
        Ns.push_back(1000 * std::pow(1.3, i));
        result = plainmc(fUnitCircle, a, b, (int)Ns[i]);
        estErrors.push_back(result[1]);
        actErrors.push_back(std::abs(analytic - result[0]));
        std::cout << Ns[i] << ", " << estErrors[i] << ", " << actErrors[i] << "\n";
    }

    //Constant function
    a = vector({-2, -2, -2});
    b = vector({2, 2 ,2});
    N = 100000;
    result = plainmc(fConstant, a, b, N);
    analytic = 64.0;

    std::cout << "\nConstant function\n";
    std::cout << resultToString(result, analytic, N);

    //Cosine function
    a = vector({0, 0, 0});
    b = vector({M_PI, M_PI, M_PI});
    N = 100000;
    result = plainmc(fCosines, a, b, N);
    analytic = 1.3932039296856768591842462603255;

    std::cout << "\nCosines example\n";
    std::cout << resultToString(result, analytic, N) << "\n\n";

    std:: cout << "--- Task B ---\n";
    a = vector({-1, -1});
    b = vector({1, 1});
    N = 100000;
    result = quasimc(fUnitCircle, a, b, N);
    analytic = M_PI;
    std::cout << resultToString(result, analytic, N);


    std::cout << "\n\n";
    std::cout << "#Quasimc errors\n";
    vector Ns2, estErrors2, actErrors2;
    for(int i = 0; i < 18; ++i) {
        Ns2.push_back(1000 * std::pow(1.3, i));
        result = quasimc(fUnitCircle, a, b, (int)Ns2[i]);
        estErrors2.push_back(result[1]);
        actErrors2.push_back(std::abs(result[0] - analytic));
        std::cout << Ns2[i] << ", " << estErrors2[i] << ", " << actErrors2[i] << "\n";
    }
    

    return 0;
}