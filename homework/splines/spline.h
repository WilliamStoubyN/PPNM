#ifndef HAVE_SPLINE_H
#define HAVE_SPLINE_H

#include"../include/vector.h"
#include"../include/matrix.h"
#include<exception>
#include<cmath>

double linterp(vector, vector, double);
int binsearch(vector, double);
double linterpInteg(vector, vector, double);

#endif