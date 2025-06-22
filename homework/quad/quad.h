#ifndef HAVE_QUAD_H
#define HAVE_QUAD_H

#include"../include/vector.h"
#include"../include/matrix.h"
#include<cmath>
#include<tuple>
#include<string>
#include<functional>
#include<exception>

double integrate(
    std::function<double(double)> f,
    double a,
    double b,
    double acc = 0.01,
    double eps = 0.01,
    double f2 = NAN,
    double f3 = NAN
);

#endif
