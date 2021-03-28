//
// Created by Vitaliy on 1/6/21.
//
#include <numeric>
#include <iomanip>
#include <ctime>
#include <vector>
#include <complex>
// quad timer

#pragma message(__VERSION__)
//TODO: try clang optimizations

intmax_t factorial (int n) {
    if (n == 0 || n == 1) return 1;
    return n * factorial(n-1);
}
// 100! = 158 digits long!
double expmy(double x, int n = 18) {
    double sum = 0;
    for (int i=0; i<=n; ++i) {
        sum += pow(x, i) / factorial(i);
    }

    return sum;
}

void testexp() {
    std::cout << "EXP(1): " << expmy(1) << std::endl;
    std::cout << "EXP(2): " << expmy(2) << std::endl;
    std::cout << "EXP(3): " << expmy(3) << std::endl;
    std::cout << "EXP(2+3): " << expmy(5) << std::endl;
    std::cout << "EXP(2) * EXP(3): " << (expmy(2) * expmy(3)) << std::endl;
    std::cout << "POW(EXP(1), 5): " << (pow(expmy(1), 5)) << std::endl;
    std::cout.precision(19);
    std::cout << "(pow(sqrt(2), 2)): " << (pow(sqrt(2), 2)) << std::endl;

    std::cout << std::fixed;
    std::srand(std::time(0));
    std::cout << "my_EXP() measurements: \n";
    measure([]{
        expmy(std::rand());
    }, 1'000'000);

    std::cout << "std::exp() measurements: \n";
    measure([]{
        exp(std::rand());
    }, 1'000'000);
}

struct MyVector {
    MyVector(int _x, int _y) : x(_x), y(_y) {};

    double x;
    double y;
};

struct MyMatrix {
    MyMatrix(std::pair<MyVector, MyVector> _vv) : vv(_vv) {};
    std::pair<MyVector, MyVector> vv;
};

MyVector rotation1(MyVector v, double angle) {
    MyVector result(0, 0);
    double norm = std::sqrt(v.x*v.x + v.y*v.y);
    double initAngle = std::atan(v.y/v.x);

    result.x = std::cos(initAngle) * std::cos(angle) + std::sin(initAngle) * std::sin(angle);
    result.y = std::cos(initAngle) * std::sin(angle);

    result.x *= norm;
    result.y *= norm;

    return result;
}

void testRotation1 () {
    std::cout << std::fixed;
    std::srand(std::time(0));

    MyVector v(3, 0);
    MyVector r = rotation1(v, M_PI/2);
    std::cout << "X:"  << std::setprecision(4) << r.x << " Y:"  << r.y << std::endl;

    measure([]{
        MyVector v1(std::rand(), std::rand());
        MyVector r = rotation1(v1, std::rand());
    }, 10'000'000);
}

MyVector rotation2(MyVector v, MyMatrix m) {
    MyVector result(v.x * m.vv.first.x + v.y * m.vv.second.x, v.x * m.vv.first.y + v.y * m.vv.second.y);
    return result;
}

void testRotation2 () {
    std::cout << std::fixed;
    std::srand(std::time(0));

    MyVector v(3, 0);
    MyMatrix m(std::pair<MyVector, MyVector>{ MyVector(0, 1), MyVector(-1, 0)});
    MyVector r = rotation2(v, m);
    std::cout << "X:"  << std::setprecision(4) << r.x << " Y:"  << r.y << std::endl;

    measure([]{
        MyVector v(std::rand(), std::rand());
        MyMatrix m({ MyVector(std::rand(), std::rand()), MyVector(std::rand(), std::rand())});
        MyVector r = rotation2(v, m);
    }, 10'000'000);
}

MyVector rotation3(MyVector v, double angle) {
    const std::complex<double> i(0, 1);
    MyVector result(0, 0);
    double norm = std::sqrt(v.x*v.x + v.y*v.y);
    double initAngle = std::atan(v.y/v.x);

    std::complex<double> euler = exp(initAngle * i);
    euler *= exp(angle * i);
    result.y = euler.imag() * norm;
    result.x = euler.real() * norm;

    return result;
}

void testRotation3 () {
    std::cout << std::fixed;
    std::srand(std::time(0));

    MyVector v(3, 0);

    MyVector r = rotation3(v, (M_PI/2));
    std::cout << "X:"  << std::setprecision(4) << r.x << " Y:"  << r.y << std::endl;

    measure([]{
        MyVector v1(std::rand(), std::rand());
        MyVector r = rotation3(v1, std::rand());
    }, 10'000'000);
}