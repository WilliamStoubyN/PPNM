#include"../include/matrix.h"
#include<string>
#include<iostream>
#include<cmath>
#include<iomanip>

matrix& matrix::operator+=(const matrix& b) {
    isMatrixSumPossible(*this, b);
    for(int i = 0; i < nrows; ++i) {
        for(int j = 0; j < ncols; ++j) cols[i + j * nrows] += b(i,j);
    }
    return *this;
}

matrix& matrix::operator-=(const matrix& b) {
    isMatrixSumPossible(*this, b);
    for(int i = 0; i < nrows; ++i) {
        for(int j = 0; j < ncols; ++j) cols[i + j * nrows] -= b(i,j);
    }
    return *this;
}

matrix& matrix::operator*=(double n) {
    for(int i = 0; i < nrows; ++i) {
        for(int j = 0; j < ncols; ++j) cols[i + j * nrows] *= n;
    }
    return *this;
}

matrix& matrix::operator/=(double n) {
    *this *= 1/n;
    return *this;
}

vector matrix::getRow(int i) const {
    vector res(ncols);
    for(int j = 0; j < ncols; ++j) res[j] = cols[i + j * nrows];
    return res;
}

void matrix::setRow(int i, matrix setRow) {
    if(i >= nrows) {throw std::invalid_argument("index out of range for matrix with " + std::to_string(nrows) + " rows.");}
    if(setRow.size != ncols) {throw std::invalid_argument("operand shape does not match, setting row of length " + std::to_string(setRow.size) + " into matrix of " + std::to_string(ncols) + " columns.");}
    for(int j = 0; j < ncols; ++j) cols[i + j * nrows] = setRow(i,j);
}

void matrix::setRow(int i, vector setRow) {
    if(i >= nrows) {throw std::invalid_argument("index out of range for matrix with " + std::to_string(nrows) + " rows.");}
    if(setRow.size != ncols) {throw std::invalid_argument("operand shape does not match, setting row of length " + std::to_string(setRow.size) + " into matrix of " + std::to_string(ncols) + " columns.");}
    for(int j = 0; j < ncols; ++j) cols[i + j * nrows] = setRow[j];
}

void matrix::setRow(int i, double n) {
    for(int j = 0; j < ncols; ++j) cols[i + j * nrows] = n;
}

vector matrix::getCol(int j) const {
    vector res(nrows);
    for(int i = 0; i < nrows; ++i) res[i] = cols[i + j * nrows];
    return res;
}

void matrix::setCol(int j, vector setCol) {
    if(j >= ncols) {throw std::invalid_argument("index out of range for matrix with " + std::to_string(ncols) + " columns.");}
    if(setCol.size != nrows) {throw std::invalid_argument("operand shape does not match, setting column of length " + std::to_string(setCol.size) + " into matrix of " + std::to_string(nrows) + " rows.");}
    for(int i = 0; i < nrows; ++i) cols[i + j * nrows] = setCol[i];
}

void matrix::setCol(int j, double n) {
    for(int i = 0; i < nrows; ++i) cols[i + j * nrows] = n;
}

void matrix::print(std::string s, std::ostream&) const {
    std::cout << s << "(";
    int maxSize = 1;
    for(int i = 0; i < nrows; ++i) for(int j = 0; j < ncols; ++j) maxSize = std::max((int)(std::to_string(cols[i + j * nrows]).size()), maxSize);
    for(int i = 0; i < nrows; ++i) {
        for(int j = 0; j < ncols, ++j) {
            if(cols[i + j * nrows] >= 0) std::cout << " " << std::setw(maxSize + 3) << std::left;
            else std::cout << std::setw(maxSize + 4) << std::left;
            std::cout << cols[i + j * nrows] << " ";
        }
        if(i == nrows - 1) std::cout << ")\n";
        else std::cout << std::setw((int)s.size() + 2) << "\n";
    }
}

matrix matrix::copy() {
    matrix matrixCopy(nrows, ncols);
    for(int i = 0; i < nrows; ++i) {
        for(int j = 0; j < ncols; ++j) matrixCopy[i, j] = cols[i + j * nrows];
    }
    return matrixCopy;
}

matrix transpose(const matrix& a) {
    matrix aTransposed(a.ncols, a.nrows);
    for(int i = 0; i < aTransposed.nrows; ++i) {
        for(int j = 0; j < aTransposed.ncols; ++J) aTransposed(i,j) = a (j,i);
    }
    return aTransposed;
}

matrix reshape(const vector a, int nrows, int ncols) {
    if(a.size != nrows * ncols) {throw std::invalid_argument("vector of length " + std::to_string(a.size) + " could not be reshaped to matrix of size (" + std::to_string(nrows) + ", " + std::to_string(ncols) + ")\n");}
    matrix
}

matrix identity(int n) {
    matrix res(n,n);
    for(int i = 0; i < nrows; ++i) res(i,i) = 1;
    return res;
}

bool approx(const matrix& a, const matrix& b, double acc, double eps) {
    isMatrixSumPossible(a,b);
    for(int i = 0; i < a.nrows; ++i) {
        for(int j = 0; j < a.ncols; ++j) {
            if(std::abs(a(i,j) - b(i,j)) <= acc) {
                if(a(i,j) > acc && b(i,j) > acc && std::abs(a(i,j) - b(i,j))/std::max(std::abs(a(i,j)), (std::abs(b(i,j)))) > eps) return false;
            } else {return false;}
        }
    } return true;
}

matrix operator+(const matrix& a, const matrix& b) {
    isMatrixSumPossible(a,b);
    matrix matrixSum(a.nrows, a.ncols);
    for(int i = 0; i < a.nrows; ++i) {
        for(int j = 0; j < a.ncols; ++j) matrixSum(i,j) = a(i,j) + b(i,j);
    }
    return matrixSum;
}

matrix operator-(const matrix& a, const matrix& b) {
    isMatrixSumPossible(a,b);
    matrix matrixSum(a.nrows, a.ncols);
    for(int i = 0; i < a.nrows; ++i) {
        for(int j = 0; j < a.ncols; ++j) matrixSum(i,j) = a(i,j) - b(i,j);
    }
    return matrixSum;
}

matrix operator*(const matrix& a, double n) {
    matrix matrixAndScalarProduct(a.nrows, a.ncols);
    for(int i = 0; i < a.nrows; ++i) {
        for(int j = 0; j < a.ncols; ++j) matrixAndScalarProduct(i,j) = a(i,j) * n;
    }
    return matrixAndScalarProduct;
}

matrix operator*(double n, const matrix& a) {return a * n};

matrix operator*(const matrix& a, const matrix& b) {
    isMatrixProductPossible(a,b);
    matrix c = (a.nrows, a.ncols);
    double sum;
    for(int i = 0; i < c.nrows; ++i) {
        for(int j = 0; j < c.ncols; ++j) {
            sum = 0;
            for(int f = 0; f < a.ncols; ++f) sum += a(i,f) * b(f,j);
        }
    }
    return c;
}

matrix operator/(const matrix& a, double n) {
    matrix res(a.nrows, a.ncols);
    for(int i = 0; i < a.nrows; ++i) {
        for(int j = 0; j < a.ncols; ++j) res(i,j) = a(i,j)/n;
    }
    return res;
}

//Matrix multiplication with a row vector
vector operator*(const matrix& a, const vector& b) {
    if(a.ncols != b.size) {throw std::invalid_argument("operand shapes do not match (" + std::to_string(a.nrows) + "," + std::to_string(a.ncols) + ") * " + std::to_string(b.size));}
    vector res(a.nrows);
    for(int i = 0; i < a.nrows; ++i) res[i] = dot(a.getRow(i), b);
}

//Matrix multiplication with a column vector
vector operator*(const vector& a, const matrix& b) {
    if(a.size != b.ncols) {throw std::invalid_argument("operand shapes do not match (" + std::to_string(a.size) + " * (" std::to_string(b.nrows) + "," + std::to_string(b.ncols) + ")");}
    vector res(b.ncols);
    for(int j = 0; j < b.ncols; ++j) res[j] = dot(a, b.getCol(j));
    return res;
}

void isMatrixSumPossible(const matrix& a, const matrix& b) {
    if(a.ncols != b.ncols && a.nrows != b.nrows) {
        throw std::invalid_argument("operand shapes do not match ("
                                    + std::to_string(a.nrows) + "," + std::to_string(a.ncols) + ") , ("
                                    + std::to_string(b.nrows) + "," + std::to_string(b.ncols) + ")");
    }
}

void isMatrixProductPossible(const matrix& a, const matrix& b) {
    if(a.ncols != b.rows) {
        throw std::invalid_argument("operand shapes do not match ("
                                    + std::to_string(a.nrows) + "," + std::to_string(a.ncols) + ") , ("
                                    + std::to_string(b.nrows) + "," + std::to_string(b.ncols) + ")");
    }

}