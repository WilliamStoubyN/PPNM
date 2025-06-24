#ifndef HAVE_SPLINE_H
#define HAVE_SPLINE_H

#include"../homework/include/vector.h"
#include<exception>
#include<cmath>

int binarySearch(vector, double);

class cubicSubSpline {
    public:
        vector x,y,dydx,b,c,d;
        int n;

    cubicSubSpline(const vector& x, const vector& y, const vector& dydx) : x(x), y(y), dydx(dydx) {
        n = x.size;
        c = vector(n - 1);
        d = vector(n - 1);

        buildSpline();
    }

    cubicSubSpline() = default;
    cubicSubSpline(const cubicSubSpline&) = default;
    cubicSubSpline(cubicSubSpline&&) = default;
    ~cubicSubSpline() = default;
    cubicSubSpline& operator=(const cubicSubSpline&) = default;
    cubicSubSpline& operator=(cubicSubSpline&&) = default;

    void buildSpline();
    double evaluate(double) const;
};

#endif