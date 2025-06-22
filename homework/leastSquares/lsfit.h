#ifndef HAVE_LSFIT_H
#define HAVE_LSFIT_H

#include"../include/vector.h"
#include"../include/matrix.h"
#include"../linear-equations/qrsolver.h"
#include<vector>
#include<functional>
#include<tuple>

std::vector lsfit(const std::vector<std::function<double(double)>>& f, const std::vector<double>&, const std::vector<double>&, const std::vector<double>)&;
// std::tuple<vector, matrix> lsfit(const std::vector<std::function<double(double)>>& f, const std::vector<double>&, const std::vector<double>&, const std::vector<double>)&;


#endif