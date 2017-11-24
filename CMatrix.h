//
// Created by abyss on 10/26/17.
//

#ifndef MATH_LAB_CMATRIX_H
#define MATH_LAB_CMATRIX_H

#include <string.h>
#include <iostream>

class CMatrix {
public:
    int nR, nC;
    double **values;
    CMatrix();

    ~CMatrix();

    enum MI {
        MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE
    };

    CMatrix(int nR, int nC, int initialization = MI_ZEROS, double
    initializationValue = 0.0);

    CMatrix(int nR, int nC, double first, ...);

    CMatrix(const CMatrix &m);

    CMatrix(double d);

    CMatrix(std::string s);

    void copy(const CMatrix &m);

    void copy(double d);

    void copy(std::string s);

    void reset();


    std::string getString();

    CMatrix operator=(const CMatrix &m);

    CMatrix operator=(double d);

    CMatrix operator=(std::string s);

    void add(const CMatrix &m);

    void operator+=(const CMatrix &m);

    void operator+=(double d);

    CMatrix operator+(const CMatrix &m);

    CMatrix operator+(double d);

    void sub(const CMatrix &m);

    void operator-=(const CMatrix &m);

    void operator-=(double d);

    CMatrix operator-(const CMatrix &m);

    CMatrix operator-(double d);

    void mul(const CMatrix &m);

    void operator*=(const CMatrix &m);

    void operator*=(double d);

    CMatrix operator*(const CMatrix &m);

    CMatrix operator*(double d);

    void div(const CMatrix &m);

    void operator/=(const CMatrix &m);

    void operator/=(double d);

    CMatrix operator/(const CMatrix &m);

    CMatrix operator/(double d);

    CMatrix operator++(); //Pre Increment
    CMatrix operator++(int); //Post Increment, int is not used
    CMatrix operator--(); //Pre Increment
    CMatrix operator--(int); //Post Increment, int is not used

    CMatrix operator-();

    CMatrix operator+();

    friend std::istream &operator>>(std::istream &is, CMatrix &C); //Stream
    friend std::ostream &operator<<(std::ostream &os, CMatrix &C); //Stream
    void setSubMatrix(int iR, int iC, const CMatrix &m);

    CMatrix getSubMatrix(int r, int c, int nr, int nc);

    CMatrix getCofactor(int r, int c);

    void addColumn(const CMatrix &m);

    void addRow(const CMatrix &m);

    double &operator[](int i) { return values[i / nC][i % nC]; }

    double &operator()(int i) { return values[i / nC][i % nC]; }

    double &operator()(int r, int c) { return values[r][c]; }

    int getn() { return nR * nC; };

    int getnR() { return nR; };

    int getnC() { return nC; };

    double getDeterminant();

    CMatrix getTranspose();

    double getInverse();
};
CMatrix operator/(double d, const CMatrix &m);
#endif //MATH_LAB_CMATRIX_H
