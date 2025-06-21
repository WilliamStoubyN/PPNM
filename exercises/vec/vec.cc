#include<cmath>
#include<string>
#include<iostream>
#include"vec.h"

//Don't need to define class again,
//Constructors and methods marked default have implementation, so no work there

vec& vec::operator+=(const vec& a) { //Addition assignment
    x += a.x;
    y += a.y;
    z += a.z;
    return *this;
}

vec& vec::operator-=(const vec& a) { //Subtraction assignment
    x -= a.x;
    y -= a.y;
    z -= a.z;
    return *this;
}

vec& vec::operator*=(double k) { //Multiplication assignment
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

vec& vec::operator/=(double k) { //Division assignment
    x /= k;
    y /= k;
    x /= k;
    return *this;
}

double vec::dot(const vec& a) { 
    return x * a.x + y * a.y + z * a.z;
}

double dot(const vec& a, const vec& b) { //Dot-prouduct between two specified vectors
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

double vec::norm() { 
    return std::sqrt(std::pow(x,2) + std::pow(y,2) + std::pow(z,2));
}

vec operator+(const vec& a, const vec& b) { //Additions operator
    return vec(a.x + b.x, a.y + b.y, a.z + b.z);
}

vec operator-(const vec& a, const vec& b) { //Subtraction operator
    return vec(a.x - b.x, a.y - b.y, a.z - b.z);
}

vec operator-(const vec& a) { //Unary subtraction/Negation operator
    return vec(-a.x, -a.y, -a.z);
}

vec operator*(const vec& a, double k) { //Multiplication operator, from the right
    return vec(a.x * k, a.y * k, a.z * k);
}

vec operator*(double k, const vec& a) { //Multiplication operator, from the left
    return vec(a.x * k, a.y * k, a.z * k);
}

vec operator/(const vec& a, double k) { //Division operator
    return vec(a.x/k, a.y/k, a.z/k);
}

bool approx(const vec& a, const vec& b, double acc, double eps) {
    if((std::abs(a.x - b.x) <= acc || std::abs(a.x - b.x)/std::max(std::abs(a.x), std::abs(b.x)) <= eps) && //All individual components must be approximately equal
    (std::abs(a.y - b.y) <= acc || std::abs(a.y - b.y)/std::max(std::abs(a.y), std::abs(b.y)) <= eps) &&
    (std::abs(a.z - b.z) <= acc || std::abs(a.z - b.z)/std::max(std::abs(a.z), std::abs(b.z)) <= eps)) {return true;}
    return false;
}

void vec::print(std::string s) const {
    std::cout << s << "(" << x << ", " << y << ", " << z << ")" << "\n";
}

std::ostream& operator<<(std::ostream& os, const vec& a) { // ToString method
    os << "(" << a.x << ", " << a.y << ", " << a.z << ")" << "\n";
    return os;
}



