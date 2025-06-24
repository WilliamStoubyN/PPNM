#ifndef HAVE_VECTOR_H
#define HAVE_VECTOR_H

#include<vector>
#include<string>
#include<iostream>
#include<initializer_list>

class vector {
    public:
        std::vector<double> data;
        int size = data.size();

        vector(int n) : data(n) {}              //parameterised ctor
        vector(std::initializer_list<double> list) : data(list.begin(), list.end()) {}
        vector() = default;                     //default ctor
        vector(const vector&) = default;        //copy ctor
        vector(vector&&) = default;             //move ctor
        ~vector() = default;                    //destructor
        vector& operator=(const vector&) = default;         //copy assignment
        vector& operator=(vector&&) = default;              //move assignment

        inline double& operator[](int i) {return data[i];}
        inline double operator[](int i) const {return data[i];}

        vector& operator+=(double);
        vector& operator-=(double);
        vector& operator*=(double);
        vector& operator/=(double);
        vector& operator+=(const vector&);
        vector& operator-=(const vector&);

        double norm() const;
        void normalize();
        vector diff() const;
        void print(std::string s = "") const;       //for debugging purposes
        vector copy() const;
        void push_back(double);
        bool isZeros() const;

        friend std::ostream& operator<<(std::ostream&, const vector&);      //toString

    };

vector operator+(const vector&, const vector&);
vector operator+(const vector&, double);
vector operator+(double, const vector&);
vector operator-(const vector&);
vector operator-(const vector&, const vector&);
vector operator-(const vector&, double);
vector operator-(double, const vector&);
vector operator*(const vector&, double);
vector operator*(double, const vector&);
vector operator/(const vector&, double);

vector project(const vector&, const vector&);       //Project vector a onto vector b

double dot(const vector&, const vector&);
bool approx(const vector& a, const vector& b, double acc = 1e-6, double eps = 1e-6);
vector linspace(double min, double max, int N);
bool areVectorsCompatible(const vector&, const vector&);

#endif
