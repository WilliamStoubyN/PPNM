#include"minimizer.h"

std::tuple<vector, int> newton(std::function<double(vector)>& phi, vector x, double acc) {
    int iterations = 0;
    vector xCopy = x.copy();

    while (iterations < 1000) {
        vector gphi = gradient(phi,xCopy);
        gphi.print("Gradient = ");
        if(gphi.norm() < acc) break;
        matrix H = hessian(phi,xCopy, gphi);
        QRSolver qrsolver(H);
        vector dx = qrsolver.solve(-gphi);
        double lambda = 1.0;

        while (lambda >= 1/1024) {
            if(phi(xCopy + lambda * dx) < phi(xCopy)) break;
            lambda /= 2;
        }
        xCopy += lambda * dx;
        ++iterations;
    }
    return std::make_tuple(xCopy, iterations);
}

vector gradient(std::function<double(vector)>& phi, vector x) {
    double phix = phi(x),       
           dxi = 0.0;
    vector gphi(x.size);

    for(int i = 0; i < x.size; ++i) {
        dxi = (1 + std::abs(x[i])) * std::pow(2, -26);
        x[i] += dxi;
        gphi[i] = (phi(x) - phix)/dxi;
        x[i] -= dxi;
    }
    return gphi;
}

matrix hessian(std::function<double(vector)>& phi, vector x, vector gphi) {
    matrix H(x.size, x.size);

    for (int j = 0; j < x.size; ++j) {
        double dxj = (1 + std::abs(x[j])) * std::pow(2, -13);
        x[j] += dxj;
        vector dgphi = gradient(phi, x) - gphi;
        for(int i = 0; i < x.size; ++i) H(i,j) = dgphi[i]/dxj;
        x[j] -= dxj;
    }
    return H;
}