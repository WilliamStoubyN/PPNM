#include"rootfinder.h"

vector newton(const std::function<vector(vector)>& f, const vector& start, double acc, vector dx) {
    vector x = start.copy();
    if(dx.isZeros()) dx = vector(x.size);
    vector fx = f(x);
    vector fStep;

    while(true) {
        if(fx.norm() <= acc) break;
        matrix J = jacobian(f, x, fx, dx);
        QRSolver JQR(J);
        vector xStep = JQR.solve(-fx);
        double lambda = 1.0;
        while(lambda >= 1.0/1024.0) {
            fStep = f(x + lambda * xStep);
            if(fStep.norm() < (1 - lambda/2) * fx.norm()) break;
            lambda /= 2;
        }
        x = x + lambda * xStep;
        fx = fStep;
    }
    return x;
}

matrix jacobian(const std::function<vector(vector)> f, vector& x, vector fx, vector dx) {
    if(fx.isZeros()) fx = f(x);
    if(dx.isZeros()) {
        for(int i = 0; i < x.size; ++i) dx[i] = std::max(1.0, std::abs(x[i])) * std::pow(2, -26);
    }
    matrix J(x.size, x.size);
    for(int i = 0; i < x.size; ++i) {
        x[i] += dx[i];
        vector df = f(x) - fx;
        for(int j = 0; j < x.size; ++j) J(j,i) = df[j]/dx[i];
        x[i] -= dx[i]; 
    }
    return J;
}