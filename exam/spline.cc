#include"spline.h"

int binarySearch(vector x, double z) {
    if(z < x[0] || z > x[x.size - 1]) throw std::invalid_argument("binsearch: bad z!");
    int i = 0, j = x.size - 1;
    while(j - i > 1) {
        int middle = (i + j)/2;
        if(z > x[middle]) {
            i = middle;
        } else {j = middle;}
    }
    return i;
}

void cubicSubSpline::buildSpline() {
    vector dx(n - 1);

    for(int i = 0; i < n -1; ++i) dx[i] = x[i + 1] - x[i];

    for(int i = 0; i < n - 1; ++i) {
        d[i] = 2/dx[i]/dx[i]/dx[i] * (y[i] - y[i + 1] + dx[i]/2 * (dydx[i + 1] + dydx[i]));
        c[i] = ((dydx[i + 1] - dydx[i])/dx[i] - 3 * d[i] * dx[i])/2;
    }
}

double cubicSubSpline::evaluate(double z) const {
    int i = binarySearch(x,z);
    double dx = z - x[i];
    return y[i] + dydx[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx; 
}

double cubicSubSpline::derivative(double z) const {
    int i = binarySearch(x,z);
    double dx = z - x[i];
    return dydx[i] + 2 * c[i] * dx + 3 * d[i] * dx * dx;
}

double cubicSubSpline::integral(double z) const {
    double sum = 0.0;
    int iMax = binarySearch(x,z);
    for(int i = 0; i < iMax; ++i) {
        double dx = x[i + 1] - x[i];
        sum += y[i] * dx + 1/2 * dydx[i] * dx * dx + 1/3 * c[i] * dx * dx * dx + 1/4 * d[i] * dx * dx * dx * dx;
    }
    double dx = z - x[iMax];
    sum += y[iMax] * dx + 1/2 * dydx[iMax] * dx * dx + 1/3 * c[iMax] * dx * dx * dx + 1/4 * d[iMax] * dx * dx * dx * dx;
    return sum;
}