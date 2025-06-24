#include"spline.h"
#include<assert.h>

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
        c[i] = 1/dx[i] * (-y[i + 1] - 2 * dydx[i] - 3/dx[i] * (y[i] - y[i + 1]));
        d[i] = 2/dx[i]/dx[i]/dx[i] * (y[i] - y[i + 1] + dx[i]/2 * (dydx[i + 1] + dydx[i]));
    }
}

double cubicSubSpline::evaluate(double z) const {
    int i = binarySearch(x,z);
    double dx = z - x[i];
    return y[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx; 
}