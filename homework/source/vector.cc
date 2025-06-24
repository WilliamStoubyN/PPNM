#include"../include/vector.h"
#include<string>
#include<iostream>
#include<cmath>
#include<stdexcept>

vector& vector::operator*=(double n) {
    for(int i = 0; i < size; ++i) data[i] *= n;
    return *this;
}

vector& vector::operator/=(double n) {
    for(auto& d : data) d /= n;
    return *this;
}

vector& vector::operator+=(const vector& a) {
    areVectorsCompatible(*this, a);
    for(int i = 0; i < size; ++i) data[i] += a.data[i];
    return *this;
}

vector& vector::operator-=(const vector& a) {
    areVectorsCompatible(*this, a);
    for(int i = 0; i < size; ++i) data[i] -= a.data[i];
    return *this;
}

vector& vector::operator+=(double n) {
    for(int i = 0; i < size; ++i) data[i] += n;
    return *this;
}

vector& vector::operator-=(double n) {
    for(int i = 0; i < size; ++i) data[i] -= n;
    return *this;
}

double vector::norm() const {
    double squaredNorm = 0;
    for(int i = 0; i < size; ++i) squaredNorm += data[i] * data[i];
    return std::sqrt(squaredNorm);
}

void vector::normalize() {
    double norm = this->norm();
    for(int i = 0; i < size; ++i) data[i] /= norm;
}

vector vector::diff() const {
    vector res(size - 1);
    for(int i = 0; i < size - 1; ++i) res[i] = data[i + 1] - data[i];
    return res;
}

void vector::print(std::string s) const {
    std::cout << s << "( ";
    for(auto d : data) std::cout << d << " ";
    std::cout << ")\n";
}

vector vector::copy() const {
    vector vectorCopy(size);
    for(int i = 0; i < size; ++i) vectorCopy[i] = data[i];
    return vectorCopy;
}

bool vector::isZeros() const {
    return approx(*this, vector(size));
}

void vector::push_back(double a) {
    data.push_back(a);
    size += 1;
}

//ToString
std::ostream& operator<<(std::ostream& os, const vector& a) {
    os << "( ";
    for(int i = 0; i < a.size; ++i) os << a[i] << " ";
    os << ")";
    return os;
}

vector operator+(const vector& a, const vector& b) {
    areVectorsCompatible(a,b);
    vector vectorSum(a.size);
    for(int i = 0; i < a.size; ++i) vectorSum[i] = a.data[i] + b.data[i];
    return vectorSum;
}

vector operator+(const vector& a, double n) {
    vector vectorSum = a.copy();
    vectorSum += n;
    return vectorSum;
}

vector operator+(double n, vector& a) {
    return a + n;
}

vector operator-(const vector& a, const vector& b) {
    areVectorsCompatible(a,b);
    vector res(a.size);
    for(int i = 0; i < a.size; ++i) res[i] = a.data[i] - b.data[i];
    return res;
}

vector operator-(const vector& a) {
    vector vectorNegation(a.size);
    for(int i = 0; i < a.size; ++i) vectorNegation[i] = -a.data[i];
    return vectorNegation;
}

vector operator-(const vector& a, double n) {
    vector vectorCopy = a.copy();
    vectorCopy -= n;
    return vectorCopy;
}

vector operator-(double n, const vector& a) {
    return (-a.copy()) + n;
}

vector operator*(const vector& a, double n) {
    vector res(a.size);
    for(int i = 0; i < a.size; ++i) res[i] = a.data[i] * n;
    return res;
}

vector operator*(double n, const vector& a) {
    vector res(a.size);
    for(int i = 0; i < a.size; ++i) res[i] = a.data[i] * n;
    return res;
}

vector operator/(const vector& a, double n) {
    vector res(a.size);
    for(int i = 0; i < a.size; ++i) res[i] = a.data[i] / n;
    return res;
}

vector project(const vector& a, const vector& b) {
    areVectorsCompatible(a,b);
    vector vectorProjected = a.copy();
    vectorProjected *= dot(a,b)/dot(a,a);
    return vectorProjected;
}

double dot(const vector& a, const vector& b) {
    areVectorsCompatible(a,b);
    double dotProduct = 0;
    for(int i = 0; i < a.size; ++i) dotProduct += a.data[i] * b.data[i];
    return dotProduct;
}

bool approx(const vector& a, const vector& b, double acc, double eps) {
    areVectorsCompatible(a,b);
    for(int i = 0; i < a.size; ++i) {
        if(std::abs(a[i] - b[i]) <= acc) {
            if(a[i] != 0 && b[i] != 0 && std::abs(a[i] - b[i])/std::max(std::abs(a[i]),(std::abs(b[i]))) > eps) return false;
        } else {return false;}
    }
    return true;
}

vector linspace(double min, double max, int N) {
    double dx = (max - min)/(N - 1);
    vector linspace(N);
    for(int i = 0; i < N; ++i) linspace[i] = min + i * dx;
    return linspace;
}

bool areVectorsCompatible(const vector& a, const vector& b) {
    if(a.size != b.size) throw std::invalid_argument("operand shapes do not match(" + std::to_string(a.size) + "," + std::to_string(b.size) + ")");
    return true;
}