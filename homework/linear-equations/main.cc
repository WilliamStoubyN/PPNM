#include"../include/vector.h"
#include"../include/matrix.h"
#include"qrsolver.h"
#include<iostream>
#include<string>
#include<assert.h>
#include<random>

int main(int argc, char** argv) {
    int n = 3, m = 2;

    std::uniform_real_distribution<double> uniformDistribution(0,1);
    std::default_random_engine randomEngine;

    for(int i = 0; i < argc; ++i) {
        std::string arg = argv[i];

        if(arg == "-n" && i + 1 < argc) n = std::stoi(argv[i + 1]);
        if(arg == "-m" && i + 1 < argc) m = std::stoi(argv[i + 1]);
    }

    std::cout << "Matrix of shape " << n << "," << m << " with uniformly random values from (0,1):\n";
    matrix A(n,m);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) A(i,j) = uniformDistribution(randomEngine);
    }

    //Generate random tall A matrix
    A.print("A = ");
    
    QRSolver qrsolver(A);

    //Factorize A into QR and check that R is upper triangular
    std::cout << "QR factorization of A:\n";
    qrsolver.decomp();
    qrsolver.Q.print("Q = ");
    qrsolver.R.print("R = ");

    //Check that Q^TQ = I
    matrix QTQ = transpose(qrsolver.Q) * qrsolver.Q;
    matrix I = identity(m);
    std::cout << "Q^TQ ?= I : " << approx(QTQ, I) << "\n";

    //Check that QR = A
    matrix QR = qrsolver.Q * qrsolver.R;
    std::cout << "QR ?= A : " << approx(QR, A) << "\n";

    //Checking solve works as intended
    vector b(n);
    for(int i = 0; i < n; ++i) b[i] = uniformDistribution(randomEngine);
    b.print("b = ");

    vector x = qrsolver.solve(b);
    std::cout << "Solution to system of linear equations AX = b is:\n";
    x.print("x = ");

    vector Ax = A * x;
    std::cout << "Ax ?= b : " << approx(Ax, b) << "\n";

    // std::cout << "Inverse of A:\n";
    // matrix AInv = qrsolver.inverse();
    // (AInv * A).print("A^-1 * A = ");
    // std::cout << "A^-1 * A ?= I : " << approx(AInv*A, I) << "\n"; 
}