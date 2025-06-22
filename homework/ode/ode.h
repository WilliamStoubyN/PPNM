#ifndef HAVE_ODE_H
#define HAVE_ODE_H

#include"../include/vector.h"
#include"../include/matrix.h"
#include<tuple>
#include<functional>
#include<exception>
#include<cmath>
#include<string>

std::tuple<vector, vector> rkStep12(
    std::function<vector(double, vector)> F,
    double h, 
    double x, 
    vector y
);

std::tuple<vector, std::vector<vector>> rkDriver(
    std::function<vector(double, vector)> F, 
    double a, 
    double b, 
    vector yInit, 
    double h0 = 0.125, 
    double acc = 0.01, 
    double eps = 0.01
);

#endif