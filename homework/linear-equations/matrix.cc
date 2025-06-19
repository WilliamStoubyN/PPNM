#include<cmath>
#include<string>
#include<iostream>
#include"matrix.h"
#define SELF (*this)

class matrix{
    public readonly int size1, size2;
    private double[] data;

    public matrix(int n, int m) {
        size1=n; size2=m;
        data = new double[size1*size2];
    }

    public double this[int i, int j] {
        get => data[i+j*size1];
        set => data[i+j*size1] = value;
    }
}