#include"spline.h"

double linterp(vector x, vector y, double z) {
    int i = binsearch(x,z);
    double dx = x[i + 1] - x[i]; if(!(dx > 0)) throw std::invalid_argument("Wrong direction");
    double dy = y[i + 1] - y[i];
    return y[i] + dy/dx * (z - x[i]);
}

int binsearch(vector x, double z) {
    if(z < x[0] || z > x[x.size - 1]) throw std::invalid_argument("binsearch: bad z :(");
    int i = 0, j = x.size - 1;
    while(j - i > 1) {
        int mid = (i + j)/2;
        if(z > x[mid]) {
            i = mid;
        } else {j = mid;}
    }
    return i;
}

double linterpInteg(vector x, vector y, double z) {
    double integral = 0;
    int iMax = binsearch(x,z);
    for(int i = 0; i < iMax; ++i) {
        double dx = x[i + 1] - x[i];
        double dy = y[i + 1] - y[i];
        double p = dy/dx;
        integral += y[i] * dx + p * dx * dx * 0.5; 
    }
    double dx = z - x[iMax];
    double dy = linterp(x, y, z) - y[iMax];
    double p = dy/dx;
    integral += y[iMax] * dx + p * dx * dx * 0.5;
    return integral;
}

void quadraticSpline::buildSpline() {
    vector dx(c.size), p(c.size);
    for(int i = 0; i < x.size - 1; ++i) {
        dx[i] = x[i + 1] - x[i];
        p[i] = (y[i + 1] - y[i])/dx[i];
    }

    for(int i = 0; i < x.size - 2; ++i) c[i + 1] = 1/dx[i + 1] * (p[i + 1] - p[i] - c[i] * dx[i]);      //forward recursion

    for(int i = x.size - 3; i >= 0; --i) c[i] = 0.5 * (c[i] + 1/dx[i] * (p[i + 1] - p[i] - c[i + 1] * dx[i + 1]));      //backward recursion

    for(int i = 0; i < c.size; ++i) b[i] = p[i] - c[i] * dx[i];
}

double quadraticSpline::evaluate(double z) const {
    int i = binsearch(x,z);
    double dx = z - x[i];
    return y[i] + b[i] * dx + c[i] * dx * dx;
}

double quadraticSpline::derivative(double z) const {
    int i = binsearch(x,z);
    double dx = z - x[i];
    return b[i] + 2 * c[i] * dx;
}

double quadraticSpline::integral(double z) const {
    int iMax = binsearch(x,z);
    double integral = 0;
    for(int i = 0; i < iMax; ++i) {
        double dx = x[i + 1] - x[i];
        integral += y[i] * dx + (1/2 * b[i] + 1/3 * c[i] * dx) * dx * dx;
    }
    double dx = z - x[iMax];
    integral += y[iMax] * dx + (1/2 * b[iMax] + 1/3 * c[iMax] * dx) * dx * dx;
    return integral;
}