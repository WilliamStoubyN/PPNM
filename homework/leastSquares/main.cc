#include"lsfit.h"
#include"../include/matrix.h"
#include"../include/vector.h"
#include<iostream>
#include<vector>
#include<functional>
#include<cmath>

int main() {
    std::vector<double> t = {1, 2, 3, 4, 6, 9, 10, 13, 15},
                        y = {117, 100, 88, 72, 53, 29.5, 25.2, 15.2, 11.1},
                        dy = {6, 5, 4, 4, 4, 3, 3, 2, 2};

    //ln(y) = ln(a) - λt
    std::vector<std::function<double(double)>> f = {
        [](double t) {return 1.0;},
        [](double t) {return t;}
    };
    
    //δln(y) = dy/y follows from error propagation, δln(y) = (dln(y)/dy) * dy
    for(int i = 0; i < (int)y.size; ++i) {
        logy = std::log(y[i]);
        logdy = dy[i]/y[i];
    }

    auto fit = lsfit(f, t, y, dy);
    vector parameters = std::get<0>(fit);

    
}