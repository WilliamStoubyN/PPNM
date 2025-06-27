#ifndef HAVE_SPLINE_H
#define HAVE_SPLINE_H

#include"../include/vector.h"
#include"../include/matrix.h"
#include<exception>
#include<cmath>

double linterp(vector, vector, double);
int binsearch(vector, double);
double linterpInteg(vector, vector, double);

class quadraticSpline {
    public:
        vector x,y,b,c;
        int n;

    quadraticSpline(const vector& x, const vector& y) : x(x), y(y) {
        n = x.size;
        b = vector(n - 1);
        c = vector(n - 1);

        buildSpline();
    }

    quadraticSpline() = default;
    quadraticSpline(const quadraticSpline&) = default;
    quadraticSpline(quadraticSpline&&) = default;
    ~quadraticSpline() = default;
    quadraticSpline& operator=(const quadraticSpline&) = default;
    quadraticSpline& operator=(quadraticSpline&&) = default;

    void buildSpline();
    double evaluate(double) const;
    double derivative(double) const;
    double integral(double) const;
};

#endif