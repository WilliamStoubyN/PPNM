#ifndef HAVE_MINIMIZER_H
#define HAVE_MINIMIZER_H

#include"../include/vector.h"
#include"../include/matrix.h"
#include<cmath>
#include<functional>
#include<string>

std::tuple<vector, int> newton(std::function<double(vector)>& phi, vector x, double acc = 1e-3);
vector gradient(std::function<double(vector)>& phi, vector x);
matrix hessian(std::function<double(vector)>& phi, vector x);


#endif
