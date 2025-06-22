#include"ode.h"

std::tuple<vector, vector> rkStep12(std::function<vector(double, vector)> f, double x, vector y, double h) {
    vector k0 = f(x,y);
    vector k1 = f(x + h/2, y + k0 * (h/2));
    vector yh = y + k1 * h;
    vector δy = (k1 - k0) * h;
    return std::tuple(yh, δy);
}

std::tuple<vector, std::vector<vector>> rkDriver(std::function<vector(double, vector)> f, double a, double b, vector yInit, double h0, double acc, double eps) {
    double x = a,
           h = h0;
    vector y = yInit.copy();

    vector xList;
    std::vector<vector> yList;
    xList.push_back(x);
    yList.push_back(y);

    std::tuple<vector, vector> stepperTupple;

    while(true) {
        if(x >= b) return std::make_tuple(xList, yList);
        if(x + h > b) h = b - x;

        stepperTupple = rkStep12(f, x, y, h);
        vector yh = std::get<0>(stepperTupple);
        vector δy = std::get<1>(stepperTupple);
        double tol = (acc + eps * yh.norm()) * std::sqrt(h/(b-a));
        double error = δy.norm();
        if(error <= tol) {
            x += h;
            y = yh;
            xList.push_back(x);
            yList.push_back(y);
        }
        if(error > 0) {h *= std::min(std::pow(tol/error, 0.25) * 0.95, 2.0);} //readjust the step-size
        else {h *= 2;}
    }
}