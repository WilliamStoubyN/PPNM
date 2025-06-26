#ifndef HAVE_SPLINE_H
#define HAVE_SPLINE_H

#include"../homework/include/vector.h"
#include<exception>
#include<cmath>

int binarySearch(vector, double);

class cubicSubSpline {
    public:
        vector x,y,yPrime,c,d;
        int n;

    cubicSubSpline(const vector& x, const vector& y, const vector& yPrime) : x(x), y(y), yPrime(yPrime) {
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
    double derivative(double) const;
    double integral(double) const;
    double doubleDerivative(double) const;
};

class quarticSubSpline {
    public:
        vector x,y,yPrime,yPrimePrime,c,d,e;
        int n;

    quarticSubSpline(const vector& x, const vector& y, const vector& yPrime) : x(x), y(y), yPrime(yPrime) {
        n = x.size;
        yPrimePrime = vector(n);
        c = vector(n - 1);
        d = vector(n - 1);
        e = vector(n - 1);

        buildSpline();
    }

    quarticSubSpline() = default;
    quarticSubSpline(const quarticSubSpline&) = default;
    quarticSubSpline(quarticSubSpline&&) = default;
    ~quarticSubSpline() = default;
    quarticSubSpline& operator=(const quarticSubSpline&) = default;
    quarticSubSpline& operator=(quarticSubSpline&&) = default;

    void buildSpline();
    double evaluate(double) const;
    double derivative(double) const;
    // double integral(double) const;
    double doubleDerivative(double) const;
};

#endif