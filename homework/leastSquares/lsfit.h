#ifndef HAVE_LSFIT_H
#define HAVE_LSFIT_H

#include"../include/vector.h"
#include"../include/matrix.h"
#include"../linearEquations/qrsolver.h"
#include<vector>
#include<functional>
#include<tuple>

//Task A
// vector lsfit(const std::vector<std::function<double(double)>>& f, const vector&, const vector&, const vector&);

//Task B
std::tuple<vector, matrix> lsfit(const std::vector<std::function<double(double)>>& f, const vector&, const vector&, const vector&);


#endif