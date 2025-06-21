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

matrix operator+(const matrix& a, const matrix& b) {
    isMatrixSumPossible(a,b);
}

matrix transpose(const matrix& a) {
    matrix aTransposed(a.ncols, a.nrows);
    for(int i = 0; i < aTransposed.nrows; ++i) {
        for(int j = 0; j < aTransposed.ncols; ++J) aTransposed(i,j) = a (j,i);
    }
    return aTransposed;
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