#include"evd.h"
#include"../include/vector.h"
#include"../include/matrix.h"
#include<random>
#include<iostream>

int main(int argc, char** argv) {
    double n = 3;

    for(int i = 0; i < argc; ++i) {
        std::string arg = argv[i];

        if(arg == "-n" && i + 1<argc) n = std::stoi(argv[i + 1]);
    }

    matrix A(n,n),
           I = identity(n);
    
    std::uniform_real_distribution<double> uniformRealDistribution(0,1);
    std::default_random_engine randomEngine;

    for(int i = 0; i < n; ++i) for(int j = 0; j < i + 1; ++j) {
        double val = uniformRealDistribution(randomEngine);
        A(i,j) = val;
        A(j,i) = val;
    }
            

    std::cout << "Random " << n << " x " << n << " matrix with values in the range [0;1]\n";
    A.print("A = ");

    std::cout << "\nEVD of A into V^T D V:\n";
    EVD evd(A);
    evd.cyclic();
    evd.V.print("V = ");
    evd.D.print("D = ");

    std::cout << "\nChecks:\n";
    std::cout << "V^TAV = D? : " << approx(transpose(evd.V) * A * evd.V, I);
    matrix K = transpose(evd.V) * A * evd.V;
    K.print("\nK = ");

    return 0;
}