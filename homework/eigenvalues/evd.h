#ifndef HAVE_EVD_H
#define HAVE_EVD_H

#include"../include/vector.h"
#include"../include/matrix.h"

class EVD {
    public:
        matrix V, D;
        // vector w;
        matrix& M;

        EVD(matrix& M_in) : M(M_in) {
            D = M_in.copy();
            V = identity(D.nrows);
            // w = vector(D.ncols);
        }//parameterized ctor

        EVD() = default;                //default ctor
        EVD(const EVD&) = default;      //copy ctor
        EVD(EVD&&) = default;           //move ctor
        ~EVD() = default;               //destructor
        EVD& operator=(const EVD&) = default;       //copy assignment
        EVD& operator=(EVD&&) = default;        //move assignment

        void timesJ(matrix&, int, int, double);     //Multiply given vector with J fom the right and update the matrix
        void Jtimes(matrix&, int, int, double);     //From the left
        void cyclic();      //Cyclic sweeping untill matrix has converged
};

#endif