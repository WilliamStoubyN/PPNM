#include"qrsolver.h"

void QRSolver::decomp() {
    vector QCol;
    for(int j = 0; j < A.ncols; ++j) {
        QCol = A.getCol(j);

        for(int f = 0; f < j; ++f) {
            R(f,j) = dot(Q.getCol(f), A.getCol(j));
            QCol -= R(f,j) * Q.getCol(f);
        }
        R(j,j) = QCol.norm();
        QCol /= R(j,j);

        Q.setCol(j, QCol);
    }
}

vector QRSolver::solve(const vector& b) const {
    vector x(A.ncols);
    vector QTb = transpose(Q) * b;
    double sum;
    for(int i = A.ncols - 1; i >= 0; --i) {
        sum = 0;
        for(int f = i + 1; f < A.ncols; ++f) sum += R(i,f) * x[f];
        x[i] = 1/R(i,i) * (QTb[i] - sum);
    }
    return x;
}

double QRSolver::determinant() {
    double res = 1;
    for(int i = 0; i < R.ncols; ++i) res *= R(i,i);
    return res;
}

matrix& QRSolver::inverse() {
    double sum;
    for(int j = 0; j < R.ncols; ++j) {
        RInv(j,j) = 1/R(j,j);
        for(int i = j -1; i >= 0; --i) {
            sum = 0;
            for(int f = i + 1; f < R.ncols; ++f) sum += R(i,f) * RInv(f,j);
            RInv(i,j) = -1/R(i,i) * sum;
        }
    }
    B = RInv * transpose(Q);
    return B;

}