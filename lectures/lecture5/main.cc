#include<iostream>
#include<cmath>
#include<complex>
#include<functional>
#include<string>

typedef std::complex<double> complex;       //Safer than doing preprocessor, supposedly

template < typename T >     //Only works on the following class, so if you want multiple templates, you need to specify it each time
void echo(T arg) {
    std::cout << "echo:" << arg << "\n";
}

void fun_of_two(std::function<double(double)> f) {
    std::cout << "f(2) = " << f(2) << "\n";
}

int main() {
    echo("string");
    echo(1);
    echo(1.23);
    complex I = std::sqrt((complex)(-1));      //No sqrt of int, so -1 gets promoted to double, but sqrt(double) cannot take a negative input, so we cast it to complex
    echo(std::sin(std::sqrt(I)));
    std::string s = "original string";
    std::function<void(void)> prints = [&s](){std::cout << "prints: s = " << s << "\n";};    //[=] means all values are captured by value, [&] means all values are captured by reference, [=, &s] means all values that are not s are captured as ref
    prints();
    s = "new string";
    prints();
    std::function<double(double)> f = [](double x){return x*x;};    //Right side of = is an anonymous function  
    fun_of_two(f);
    fun_of_two( [](double x){return x*x;});
    return 0;
}