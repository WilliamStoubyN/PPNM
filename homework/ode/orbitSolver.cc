#include"../include/vector.h"
#include"../include/matrix.h"
#include"ode.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>

std::function<vector(double, vector)> equatorialMotion(double epsilon) {
    std::function<vector(double, vector)> f = [=](double x, const vector& y) {
        vector u(2);
        u[0] = y[1];
        u[1] = 1 - y[0] + epsilon * y[0] * y[0];
        return u;
    };
    return f;
};

int main() {
    vector u0(2);
    double a = 0.0,
           b = 25.0;
    double acc = 0.001,
           eps = 0.001;

    //Circular motion
    u0[0] = 1.0, u0[1] = 0.001;
    std::tuple<vector, std::vector<vector>> circularOrbit = rkDriver(equatorialMotion(0.0), a, b, u0, 0.125, acc ,eps);
    vector xs1 = std::get<0>(circularOrbit);
    std::vector<vector> ys1 = std::get<1>(circularOrbit);

    //Elliptical motion
    u0[0] = 1.0, u0[1] = -0.5;
    std::tuple<vector, std::vector<vector>> ellipticalOrbit = rkDriver(equatorialMotion(0.0), a, b, u0, 0.125, acc ,eps);
    vector xs2 = std::get<0>(ellipticalOrbit);
    std::vector<vector> ys2 = std::get<1>(ellipticalOrbit);

    //Relativistic precession of the orbit
    u0[0] = 1.0, u0[1] = -0.5;
    acc = 0.01, eps = 0.01;
    std::tuple<vector, std::vector<vector>> precession = rkDriver(equatorialMotion(0.1), a, b, u0, 0.125, acc ,eps);
    vector xs3 = std::get<0>(precession);
    std::vector<vector> ys3 = std::get<1>(precession);

    std::cout << "#Circular motion\n";
    for(int i = 0; i < xs1.size; ++i) std::cout << xs1[i] << " " << ys1[i][0] << "\n";
    std::cout << "\n\n";

    std::cout << "#Elliptical motion\n";
    for(int i = 0; i < xs2.size; ++i) std::cout << xs2[i] << " " << ys2[i][0] << "\n";
    std::cout << "\n\n";

    std::cout << "#Precession\n";
    for(int i = 0; i < xs3.size; ++i) std::cout << xs3[i] << " " << ys3[i][0] << "\n";
    std::cout << "\n\n";

    return 0;
}