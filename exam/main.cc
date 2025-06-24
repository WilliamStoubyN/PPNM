#include"spline.h"
#include"../include/vector.h"
#include<iostream>
#include<cmath>

int main() {
    int N = 15;
    vector xs(N), ys(N), dydx(N);

    for(int i = 0; i < N; ++i) {
        xs[i] = 15.0/N * i;
        ys[i] = std::sin(xs[i]);
        dydx[i] = std::cos(xs[i]); 
    }




    return 0;
}