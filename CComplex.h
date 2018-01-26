//
// Created by abyss on 1/27/18.
//

#ifndef MATH_LAB_CCOMPLEX_H
#define MATH_LAB_CCOMPLEX_H

#include <string>
#include <istream>

using namespace std;

class CComplex {
    double R;
    double I;
public:
    CComplex();

    CComplex(double R, double I);

    CComplex(CComplex &C);

    void copy(CComplex &C);

    std::string getString();

    double magnitude();

    double angle();

    void negative();

    double real();

    double imaginary();

    static CComplex addComplex(CComplex &A,const CComplex &B);

    void add(CComplex &C);

    CComplex &operator=(CComplex &C);

    CComplex operator=(double);

    void operator+=(CComplex &C);

    void operator+=(double D);

    CComplex operator+(CComplex &C);

    CComplex operator+(double D);

    CComplex operator-();

    operator const string();

    CComplex operator++();
    CComplex operator++(int);
    double operator[](string name);
    double operator()(string name, string info = "");

    friend std::istream &operator>>(std::istream &is, CComplex &C);

    friend std::ostream &operator<<(std::ostream &os, CComplex &C);

    ~CComplex();
};

CComplex operator*(CComplex& A, CComplex& B);
#endif //MATH_LAB_CCOMPLEX_H
