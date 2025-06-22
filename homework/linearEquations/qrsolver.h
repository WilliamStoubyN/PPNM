#ifndef HAVE_QRSOLVER_H
#define HAVE_QRSOLVER_H

#include"../include/matrix.h"
#include"../include/vector.h"
#include<cmath>

class QRSolver {
    public:
        matrix Q, R;
        matrix& A;
        matrix B;
        matrix RInv;

        QRSolver(matrix& A_in) : A(A_in) {
            Q = A.copy();
            R = matrix(A.ncols, A.ncols);
            decomp();
        } //parameterized ctor

        QRSolver() = default;
        QRSolver(const QRSolver&) = default;
        QRSolver(QRSolver&&) = default;
        ~QRSolver() = default;
        QRSolver& operator=(const QRSolver&) = default;
        QRSolver& operator=(QRSolver&&) = default;

        void decomp();                          //calculate and set Q and R matrices
        vector solve(const vector&) const;      //solve a system of linear equations Ax = b
        matrix& inverse();                      //calculate the inverse of A
        double determinant();                   //calculate the determinant of A
};

#endif