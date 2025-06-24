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

