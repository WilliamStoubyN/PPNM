#include<iostream>
#include<cmath>
using namespace std;

int main() {
    //Task 1:
    // int i = 0;
    // while(i + 1 > i) {
    //     i++;
    // }
    // std::cout << "max int = " << i << std::endl;

    // i = 0;
    // while(i - 1 < i) {i--;}
    // std::cout << "min int = " << i << std::endl;
    
    //Task 2:
    double x = 1;
    while(1+x != 1) {x /= 2;}
    std::cout << "double machine epsilon = " << 2*x << std::endl;

    // float y = 1;
    // while((float)1 + y != 1) { y /= 2; }
    // std::cout << "float machine epsilon = " << 2*y << std::endl;

    //Task 3:
    // double tiny = x/2;
    double tiny = cmath::pow(2,-52);
    double a = 1 + tiny + tiny;
    double b = tiny + tiny + 1;

    bool test1 = a == b;
    bool test2 = a > 1;
    bool test3 = b > 1;

    std::cout << "a == b : " << test1 << std::endl;
    std::cout << "a > 1 : " << test2 << std::endl;
    std::cout << "b > 1 : " << test3 << std::endl;


    
    return 0;
}