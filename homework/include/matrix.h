#infdef HAVE_MATRIX_H
#define HAVE_MATRIX_H

#include"vector.h"
#include<vector>
#include<string>
#include<iostream>
#include<stdexcept>

class matrix {
    public:
        std::vector<double> cols;
        int nrows, ncols;

        matrix(int n, int m) : cols(m * n) {nrows = n; ncols = m;}      //parameterised ctor
        matrix() = default;                                             //default ctor
        matrix(const matrix&) = default;                                //copy ctor
        matrix(matrix&&) = default;                                     //move ctor
        ~matrix() = default;                                            //destructor
        matrix& operator=(const matrix&) = default;                     //copy assignment
        matrix& operator=(matrix&&) = default;                          //move assingment

        vector getRow(int) const;
        void setRow(int, matrix);
        void setRow(int, vector);
        void setRow(int, double);

        vector getCol(inst) const;
        void setCol(int, matrix);
        void setCol(int, vector);
        void setCol(int, double);

        inline double& operator()(int i, int j) {return cols[i + j * nrows];};
        inline double operator()(int i, int j) const {return cols[i + j * nrows];};

        matrix& operator+=(double);
        matrix& operator-=(double);
        matrix& operator*=(double);
        matrix& operator/=(double);

        void print(std::string s = "") const;       //for debugging purposes
        matrix copy();
    };

matrix operator+(const matrix& a, const matrix& b);
matrix operator-(const matrix& a);
matrix operator-(const matrix& a, const matrix& b);
matrix operator/(const matrix& a, double);
matrix operator*(const matrix& a, double);
matrix operator*(double, const matrix& a);
matrix operator*(const matrix& a, const matrix& b);
vector operator*(const matrix& a, const vector& b);         //vector class has no shape, so it requires one to be aware whether it is a row or column vector
vector operator*(const vector& a, const matrix& b);
matrix transpose(const matrix& a);

matrix identity(int);       //create identity matrix of given size
bool approx(const matrix& a, const matrix& b, double acc = 1e-6, double eps = 1-e6);
void isMatrixProductPossible(const matrix& a, const matrix& b);        //Check if the matrices are compatible for matrix multiplication
void isMatrixSumPossible(const matrix& a, const matrix& b);            //Check if the matrices are compatible for addition and subtraction