//
// Created by abyss on 10/26/17.
//

#ifndef MATH_LAB_CMATRIX_H
#define MATH_LAB_CMATRIX_H

#include <cstring>
#include <iostream>
#include <cmath>

class CMatrix {
    char name;
    int nR, nC;
    double **values;
public:
    CMatrix();

    ~CMatrix();

    enum MI {
        MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE
    };

    CMatrix(int nR, int nC, int initialization = MI_ZEROS, double initializationValue = 0.0);

    CMatrix(int nR, int nC, double first, ...);

    CMatrix(const CMatrix &m);

    CMatrix(double d);

    CMatrix(std::string s);

    CMatrix(char name);

    void setName(char name);

    char getName();

    CMatrix &operator=(const CMatrix &m);

    CMatrix &operator=(double &d);

    CMatrix &operator=(const char*);

    void operator+=(const CMatrix &m);

    void operator+=(double d);

    CMatrix operator+(const CMatrix &m);

    CMatrix operator+(double d);

    void operator-=(const CMatrix &m);

    void operator-=(double d);

    CMatrix operator-(const CMatrix &m);

    CMatrix operator-(double d);

    void operator*=(const CMatrix &m);

    void operator*=(double d);

    CMatrix operator*(const CMatrix &m);

    CMatrix operator*(double &d);

    void operator/=(const CMatrix &m);

    void operator/=(double d);

    CMatrix operator/(const CMatrix &m);

    CMatrix operator/(double d);

    CMatrix &operator++(); //Pre Increment
    CMatrix operator++(int); //Post Increment, int is not used
    CMatrix &operator--(); //Pre Increment
    CMatrix operator--(int); //Post Increment, int is not used

    CMatrix operator-();

    CMatrix operator+();

    friend std::istream &operator>>(std::istream &is, CMatrix &C); //Stream
    friend std::ostream &operator<<(std::ostream &os, CMatrix &C); //Stream
    void setSubMatrix(int iR, int iC, const CMatrix &m);

    CMatrix getSubMatrix(int r, int c, int nr, int nc);

    const CMatrix getCofactorMatrix(int r, int c) const;

    void addColumn(const CMatrix &m);

    void addRow(const CMatrix &m);

    double &operator[](int i) { return values[i / nC][i % nC]; }

    double &operator()(int i) { return values[i / nC][i % nC]; }

    double &operator()(int r, int c) { return values[r][c]; }

    int getn() { return nR * nC; };

    int getnR() { return nR; };

    int getnC() { return nC; };

    static CMatrix augment(CMatrix &, CMatrix &);

    CMatrix gaussianEliminate();

    CMatrix rowReduceFromGaussian();

    CMatrix getTranspose();

    CMatrix getInverse();

    friend double det(CMatrix &m);

private:
    void copy(const CMatrix &m);

    void copy(double &d);

    void copy(std::string &s);

    void reset();

    std::string getString();

    void sub(const CMatrix &m);

    void mul(const CMatrix &m);

    void add(const CMatrix &m);

    void div(const CMatrix &m);

    void swapRows(int, int);
};

CMatrix operator/(double d, CMatrix &m);

CMatrix operator*(double d, CMatrix &m);

CMatrix operator+(double d, CMatrix &m);

CMatrix operator-(double d, CMatrix &m);

#endif //MATH_LAB_CMATRIX_H
