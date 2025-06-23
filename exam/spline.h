#ifndef HAVE_SPLINE_H
#define HAVE_SPLINE_H

#include"../include/vector.h"
#include<exception>
#include<cmath>

int binarySearch(vector, double);

class cubicSubSpline() {
    public:
        vector x,y,b,c,d;

    cubicSubSpline(const vector& x, const vector& y) : x(x), y(y) {
        b = vector(x.size - 1);
        c = vector(x.size - 1);
        d = vector(x.size - 1);
    }

    cubicSubSpline() = default;
    cubicSubSpline(const cubicSubSpline&) = default;
    cubicSubSpline(cubicSubSpline&&) = default;
    ~cubicSubSpline() = default;
    cubicSubSpline& operator=(const cubicSubSpline&) = default;
    cubicSubSpline& operator=(cubicSubSpline&&) = default;

    void buildSpline();
    double eval(double) const;
};

#endif