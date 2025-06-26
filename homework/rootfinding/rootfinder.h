#ifndef HAVE_ROOTFINDER_H
#define HAVE_ROOTFINDER_H

#include"../include/vector.h"
#include"../include/matrix.h"
#include"../linearEquations/qrsolver.h"
#include<cmath>
#include<functional>
#include<string>
#include<iostream>

vector newton(const std::function<vector(vector)>&, const vector&, double acc = 0.01, vector dx = vector({0.0}));

matrix jacobian(const std::function<vector(vector)>, vector&, vector fx = vector({0.0}), vector dx = vector({0.0}));

#endif