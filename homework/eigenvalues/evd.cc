#include"evd.h"
#include<cmath>

void EVD::timesJ(matrix& A, int p, int q, double theta) {
    double c = std::cos(theta), 
           s = std::sin(theta);

    for(int i = 0; i < A.nrows; ++i) {
        double aip = A(i,p),
               aiq = A(i,q);
        A(i,p) = c * aip - s * aiq;
        A(i,q) = s * aip + c * aiq;
    }
}

void EVD::Jtimes(matrix& A, int p, int q, double theta) {
    double c = std::cos(theta), 
           s = std::sin(theta);

    for(int j = 0; j < A.nrows; ++j) {
        double apj = A(p,j),
               aqj = A(q,j);
        A(p,j) = c * apj + s * aqj;
        A(q,j) = -s * apj + c * aqj;
    }
}

void EVD::cyclic() {
    bool changed = false;
    do {
        changed = false;
        for(int i = 0; i < D.nrows - 1; ++i) {
            for(int j = i + 1; j < D.nrows; ++j) {
                double apq = D(i,j),
                       app = D(i,i),
                       aqq = D(j,j);
                double theta = 0.5 * std::atan2(2 * apq, aqq-app);
                double c = std::cos(theta),
                       s = std::sin(theta);
                double new_app = c * c * app - 2 * s * c * apq + s * s * aqq;
                double new_aqq = s * s * app + 2 * s * c * apq + c * c * aqq;
                if(new_app != app || new_aqq != aqq) 
                    { //do a sweep
                    changed = true;
                    timesJ(D,i,j,theta); //A + A * J
                    Jtimes(D,i,j,-theta); //A + J^T * A
                    timesJ(V,i,j,theta); //V <-- V * J
                    }   
            }
        } 
    } while(changed);
}