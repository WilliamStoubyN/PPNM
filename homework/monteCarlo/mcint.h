#ifndef HAVE_MCINT_H
#define HAVE_MCINT_H

#include"../include/vector.h"
#include<cmath>
#include<string>
#include<functional>

vector plainmc(std::function<double(vector)>& f, vector a, vector b, int N);

#endif