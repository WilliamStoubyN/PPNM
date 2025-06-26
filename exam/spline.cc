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

    for(int i = 0; i < n - 1; ++i) {
        dx[i] = x[i + 1] - x[i];
        d[i] = 2/dx[i]/dx[i]/dx[i] * (y[i] - y[i + 1] + dx[i]/2 * (yPrime[i + 1] + yPrime[i]));
        c[i] = ((yPrime[i + 1] - yPrime[i])/dx[i] - 3 * d[i] * dx[i])/2;
    }
}

double cubicSubSpline::evaluate(double z) const {
    int i = binarySearch(x,z);
    double dx = z - x[i];
    return y[i] + yPrime[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx; 
}

double cubicSubSpline::derivative(double z) const {
    int i = binarySearch(x,z);
    double dx = z - x[i];
    return yPrime[i] + 2 * c[i] * dx + 3 * d[i] * dx * dx;
}

// double cubicSubSpline::doubleDerivative(double z) const {
//     int i = binarySearch(x,z);
//     double dx = z - x[i];
//     return  2 * c[i] + 6 * d[i] * dx;
// }

double cubicSubSpline::integral(double z) const {
    double sum = 0.0;
    int iMax = binarySearch(x,z);
    for(int i = 0; i < iMax; ++i) {
        double dx = x[i + 1] - x[i];
        sum += y[i]*dx + 1/2 * yPrime[i]*dx*dx + 1/3 * c[i]*dx*dx*dx + 1/4 * d[i]*dx*dx*dx*dx;
    }
    double dx = z - x[iMax];
    sum += y[iMax]*dx + 1/2 * yPrime[iMax]*dx*dx + 1/3 * c[iMax]*dx*dx*dx + 1/4 * d[iMax]*dx*dx*dx*dx;
    return sum;
}

void quarticSubSpline::buildSpline() {
    vector dx(n - 1);

    for(int i = 0; i < n - 1; ++i) {
        dx[i] = x[i + 1] - x[i];
        yPrimePrime[i] = (yPrime[i + 1] - yPrime[i])/dx[i];
    }

    // for(int i = 0; i < n - 1; ++i) {
    //     yPrimePrime[i] = (yPrime[i + 1] - yPrime[i])/dx[i];
    // }

    // yPrimePrime[0] = 0;
    // yPrimePrime[1] = 0;
    // yPrimePrime[n - 1] = 0;
    // yPrimePrime[n - 2] = 0;

    // for(int i = 0; i < n - 2; ++i) {
    //     yPrimePrime[i] = (yPrime[i + 1] - yPrime[i])/dx[i];
    // }

    for(int i =  0; i < n - 1; ++i) {
        d[i] = 2/dx[i]/dx[i]/dx[i] * (y[i] - y[i + 1] + dx[i]/2 * (yPrime[i + 1] + yPrime[i]));
        c[i] = ((yPrime[i + 1] - yPrime[i])/dx[i] - 3 * d[i] * dx[i])/2;
        e[i] = (yPrimePrime[i + 1] - 2 * c[i] - 6 * d[i] * dx[i])/dx[i]/dx[i]/2;
    }
}

double quarticSubSpline::evaluate(double z) const {
    int i = binarySearch(x,z);
    double dx1 = z - x[i];
    double dx2 = z - x[i];
    return y[i] + yPrime[i] * dx1 + c[i] * dx1 * dx1 + d[i] * dx1 * dx1 * dx1 + e[i] * dx1 * dx1 * dx2 * dx2; 
}

double quarticSubSpline::derivative(double z) const {
    int i = binarySearch(x,z);
    double dx1 = z - x[i];
    double dx2 = z - x[i];
    return yPrime[i] + 2 * c[i] * dx1 + 3 * d[i] * dx1 * dx1 + 2 * e[i] * dx1 * dx2 * (x[i] + x[i + 1] - 2 * z);
}

double quarticSubSpline::doubleDerivative(double z) const {
    int i = binarySearch(x,z);
    double dx1 = z - x[i];
    // double dx2 = z - x[i + 1];
    return 2 * c[i] + 6 * d[i] * dx1 + 2 * e[i] * (x[i] * x[i] + 4 * x[i] * x[i + 1] - 6 * x[i] * z + x[i + 1] * x[i + 1] - 6 * x[i + 1] * z + 6 * z * z);
}
