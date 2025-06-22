#include"quad.h"

double integrate(std::function<double(double)> f, double a, double b, double acc, double eps, double f2, double f3) {
    double h = b - a;
    if(std::isnan(f2)) {
        f2 = f(a + 2 * h/6);
        f3 = f(a + 4 * h/6);
    }
    double f1 = f(a + h/6),
           f4 = f(a + 5 * h/6);

    double Q = (2 * f1 + f2 + f3 + 2 * f4)/6 * (b - a); //higher order
    double q = (f1 + f2 + f3 + f4)/4 * (b - a); //lower order
    double error = std::abs(Q - q);
    double tolerance = acc + eps * std::abs(Q);
    if(error <= tolerance) {return Q;}
    else {
        auto integral1 = integrate(f, a, (a+b)/2.0, acc/std::sqrt(2), eps, f1, f2);
        auto integral2 = integrate(f, (a+b)/2.0, b, acc/std::sqrt(2), eps, f3, f4);
        double integral = integral1 + integral2;
        return integral;
    }
}