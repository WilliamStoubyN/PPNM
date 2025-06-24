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

// void cubicSubSpline::buildSpline() {
//     vector dx(n - 1);

//     for(int i = 0; i < n - 1; ++i) dx[i] = x[i + 1] - x[i];

//     for(int i = 0; i < n - 1; ++i) {
//         d[i] = 2/dx[i]/dx[i]/dx[i] * (y[i] - y[i + 1] + dx[i]/2 * (dydx[i + 1] + dydx[i]));
//         c[i] = ((dydx[i + 1] - dydx[i])/dx[i] - 3 * d[i] * dx[i])/2;
//     }
// }

void cubicSubSpline::buildSpline() {
    vector dx(n - 1);

    for(int i = 0; i < n - 1; ++i) dx[i] = x[i + 1] - x[i];

    b[0] = dydx[0];
    b[1] = (dydx[0] + dydx[1])/2;
    b[n - 1] = (dydx[n - 2]);
    b[n - 2] = (dydx[n - 2] - dydx[n - 3])/2;

    for(int i = 2; i < n - 2; ++i) {
        double w1, w2;
        w1 = std::abs(dydx[i + 1 - dydx[i]]);
        w2 = std::abs(dydx[i - 1] - dydx[i - 2]);
        if(w1 + w2 == 0) b[i] = (dydx[i - 1] + dydx[i])/2;
        else b[i] = (w1 * dydx[i - 1] + w2 * dydx[i])/(w1 + w2);
    }

    for(int i = 0; i < n - 1; ++i) {
        d[i] = 2/dx[i]/dx[i]/dx[i] * (y[i] - y[i + 1] + dx[i]/2 * (b[i + 1] + b[i]));
        c[i] = ((b[i + 1] - b[i])/dx[i] - 3 * d[i] * dx[i])/2;
    }
}

double cubicSubSpline::evaluate(double z) const {
    int i = binarySearch(x,z);
    double dx = z - x[i];
    return y[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx; 
}

double cubicSubSpline::derivative(double z) const {
    int i = binarySearch(x,z);
    double dx = z - x[i];
    return b[i] + 2 * c[i] * dx + 3 * d[i] * dx * dx;
}


double cubicSubSpline::doubleDerivative(double z) const {
    int i = binarySearch(x,z);
    double dx = z - x[i];
    return  2 * c[i] + 6 * d[i] * dx;
}

double cubicSubSpline::integral(double z) const {
    double sum = 0.0;
    int iMax = binarySearch(x,z);
    for(int i = 0; i < iMax; ++i) {
        double dx = x[i + 1] - x[i];
        sum += y[i] * dx + 1/2 * b[i] * dx * dx + 1/3 * c[i] * dx * dx * dx + 1/4 * d[i] * dx * dx * dx * dx;
    }
    double dx = z - x[iMax];
    sum += y[iMax] * dx + 1/2 * b[iMax] * dx * dx + 1/3 * c[iMax] * dx * dx * dx + 1/4 * d[iMax] * dx * dx * dx * dx;
    return sum;
}

void quarticSubSpline::buildSpline() {
    vector dx(n - 1);

    for(int i = 0; i < n - 1; ++i) dx[i] = x[i + 1] - x[i];

    //TODO
    //Solve the system of 3 linear equations for the coefficients
    for(int i =  0; i < n - 1; ++i) {

    }
}