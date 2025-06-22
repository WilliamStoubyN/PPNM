#include"lsfit.h"

vector lsfit(const std::vector<std::function<double(double)>>& f, const vector& x, const vector& y, const vector& dy) {
    matrix A(x.size, f.size());
    vector b(y.size);

    //Using Eq. 3.32 from the book
    for(int i = 0; i < (int) x.size; ++i) {
        for(int j = 0; j < (int) f.size(); ++j) {
            A(i,j) = f[j](x[i])/dy[i];
        }
        b[i] = y[i]/dy[i];
    }
    QRSolver qrsolver(A);
    qrsolver.decomp();
    vector parameters = qrsolver.solve(b);

    return parameters;
}