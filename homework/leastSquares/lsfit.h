#ifndef HAVE_LSFIT_H
#define HAVE_LSFIT_H

#include"../include/vector.h"
#include"../include/matrix.h"
#include"../linearEquations/qrsolver.h"
#include<vector>
#include<functional>
#include<tuple>

vector lsfit(const std::vector<std::function<double(double)>>& f, const vector&, const vector&, const vector&);
// std::tuple<vector, matrix> lsfit(const std::vector<std::function<double(double)>>& f, const std::vector<double>&, const std::vector<double>&, const std::vector<double>&);


#endif