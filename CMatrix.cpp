//
// Created by abyss on 10/26/17.
//

#include "CMatrix.h"
#include "../../../../../usr/include/c++/7.2.0/cstdlib"
#include <cstdarg>
#include <cstring>
#include <algorithm>

CMatrix::CMatrix() {
    nR = nC = 0;
    values = NULL;
}

CMatrix::~CMatrix() {
    reset();
}

CMatrix::CMatrix(int nR, int nC, int initialization, double initializationValue) {
    this->nR = nR;
    this->nC = nC;
    if ((nR * nC) == 0) {
        values = NULL;
        return;
    }
    values = new double *[nR];
    for (int iR = 0; iR < nR; iR++) {
        values[iR] = new double[nC];
        for (int iC = 0; iC < nC; iC++) {
            switch (initialization) {
                case MI_ZEROS:
                    values[iR][iC] = 0;
                    break;
                case MI_ONES:
                    values[iR][iC] = 1;
                    break;
                case MI_EYE:
                    values[iR][iC] = (iR == iC) ? 1 : 0;
                    break;
                case MI_RAND:
                    values[iR][iC] = (rand() % 1000000) / 1000000.0;
                    break;
                case MI_VALUE:
                    values[iR][iC] = initializationValue;
                    break;
            }
        }
    }
}

CMatrix::CMatrix(int nR, int nC, double first, ...) {
    this->nR = nR;
    this->nC = nC;
    if ((nR * nC) == 0) {
        values = NULL;
        return;
    }
    values = new double *[nR];
    va_list va;
    va_start(va, first);
    for (int iR = 0; iR < nR; iR++) {
        values[iR] = new double[nC];
        for (int iC = 0; iC < nC; iC++) {
            values[iR][iC] = (iC == 0 && iR == 0) ? first : va_arg(va, double);
        }
    }
    va_end(va);
}

CMatrix::CMatrix(const CMatrix &m) {
    nR = nC = 0;
    values = NULL;
    copy(m);
}

CMatrix::CMatrix(std::string s) {
    nR = nC = 0;
    values = NULL;
    copy(s);
}

void CMatrix::copy(const CMatrix &m) {
    reset();
    this->nR = m.nR;
    this->nC = m.nC;
    if ((nR * nC) == 0) {
        values = NULL;
        return;
    }
    values = new double *[nR];
    for (int iR = 0; iR < nR; iR++) {
        values[iR] = new double[nC];
        for (int iC = 0; iC < nC; iC++) {
            values[iR][iC] = m.values[iR][iC];
        }
    }
}

CMatrix::CMatrix(double d) {
    nR = nC = 0;
    values = NULL;
    copy(d);
}

void CMatrix::copy(double d) {
    reset();
    this->nR = 1;
    this->nC = 1;
    values = new double *[1];
    values[0] = new double[1];
    values[0][0] = d;
}

void CMatrix::copy(std::string s) {
    reset();
    char *buffer = new char[s.length() + 1];
    strcpy(buffer, s.c_str());
    char *lineContext;
    char *lineSeparators = ";\r\n";
    char *line = strtok_r(buffer, lineSeparators, &lineContext);
    while (line) {
        CMatrix row;
        char *context;
        char *separators = " []";
        char *token = strtok_r(line, separators, &context);
        while (token) {
//            CMatrix&& m = std::move(atof(token));
            CMatrix item = atof(token);
            row.addColumn(item);
            token = strtok_r(NULL, separators, &context);
        }
        if (row.nC > 0 && (row.nC == nC || nR == 0))
            addRow(row);
        line = strtok_r(NULL, lineSeparators, &lineContext);
    }
    delete[] buffer;
}

void CMatrix::reset() {
    if (values) {
        for (int i = 0; i < nR; i++)
            delete[] values[i];
        delete[] values;
    }
    nR = nC = 0;
    values = NULL;
}

std::string CMatrix::getString() {
    std::string s;
    for (int iR = 0; iR < nR; iR++) {
        for (int iC = 0; iC < nC; iC++) {
            char buffer[50];
            snprintf(buffer, 50, "%g\t", values[iR][iC]);
            s += buffer;
        }
        s += "\n";
    }
    return s;
}

CMatrix CMatrix::operator=(const CMatrix &m) {
    copy(m);
    return *this;
}

CMatrix CMatrix::operator=(double d) {
    copy(d);
    return *this;
}

CMatrix CMatrix::operator=(std::string s) {
    copy(s);
    return *this;
}

void CMatrix::add(const CMatrix &m) {
    if (nR != m.nR || nC != m.nC)
        throw ("Invalid matrix dimension");
    for (int iR = 0; iR < nR; iR++)
        for (int iC = 0; iC < nC; iC++)
            values[iR][iC] += m.values[iR][iC];
}

void CMatrix::operator+=(const CMatrix &m) {
    add(m);
}

void CMatrix::operator+=(double d) {
//    CMatrix&& m = std::move(CMatrix(nR, nC, MI_VALUE, d));
    add(CMatrix(nR, nC, MI_VALUE, d));
}

CMatrix CMatrix::operator+(const CMatrix &m) {
    CMatrix r = *this;
    r += m;
    return r;
}

CMatrix CMatrix::operator+(double d) {
    CMatrix r = *this;
    r += d;
    return r;
}

void CMatrix::sub(const CMatrix &m) {
    if (nR != m.nR || nC != m.nC)
        throw ("Invalid matrix dimension");
    for (int iR = 0; iR < nR; iR++)
        for (int iC = 0; iC < nC; iC++)
            values[iR][iC] -= m.values[iR][iC];
}

void CMatrix::operator-=(const CMatrix &m) {
    sub(m);
}

void CMatrix::operator-=(double d) {
//    CMatrix&& m = std::move(CMatrix(nR, nC, MI_VALUE, d));
    sub(CMatrix(nR, nC, MI_VALUE, d));
}

CMatrix CMatrix::operator-(const CMatrix &m) {
    CMatrix r = *this;
    r -= m;
    return r;
}

CMatrix CMatrix::operator-(double d) {
    CMatrix r = *this;
    r -= d;
    return r;
}

void CMatrix::mul(const CMatrix &m) {
    if (nR != m.nR || nC != m.nC)
        throw ("Invalid matrix dimension");
    CMatrix r(nR, m.nC);
    for (int iR = 0; iR < r.nR; iR++)
        for (int iC = 0; iC < r.nC; iC++) {
            r.values[iR][iC] = 0;
            for (int k = 0; k < m.nC; k++)
                r.values[iR][iC] += values[iR][k] * m.values[k][iC];
        }
    copy(r);
}

void CMatrix::operator*=(const CMatrix &m) {
    mul(m);
}

void CMatrix::operator*=(double d) {
    for (int iR = 0; iR < nR; iR++)
        for (int iC = 0; iC < nC; iC++)
            values[iR][iC] *= d;
}

CMatrix CMatrix::operator*(const CMatrix &m) {
    CMatrix r = *this;
    r *= m;
    return r;
}

CMatrix CMatrix::operator*(double d) {
    CMatrix r = *this;
    r *= d;
    return r;
}

void CMatrix::div(const CMatrix &m) {
    if (nR != m.nR || nC != m.nC)
        throw ("Invalid matrix dimension");
    CMatrix r(nR, m.nC);
    for (int iR = 0; iR < r.nR; iR++)
        for (int iC = 0; iC < r.nC; iC++) {
            r.values[iR][iC] = 0;
            for (int k = 0; k < m.nC; k++)
                r.values[iR][iC] += values[iR][k] / m.values[k][iC];
        }
    copy(r);
}

void CMatrix::operator/=(const CMatrix &m) {
    div(m);
}

void CMatrix::operator/=(double d) {
    for (int iR = 0; iR < nR; iR++)
        for (int iC = 0; iC < nC; iC++)
            values[iR][iC] /= d;
}

CMatrix CMatrix::operator/(const CMatrix &m) {
    CMatrix r = *this;
    r /= m;
    return r;
}

CMatrix CMatrix::operator/(double d) {
    CMatrix r = *this;
    r /= d;
    return r;
}

CMatrix CMatrix::operator++() {
//    CMatrix&& m = std::move(CMatrix(nR, nC, MI_VALUE, 1.0));
    add(CMatrix(nR, nC, MI_VALUE, 1.0));
    return *this;
}

CMatrix CMatrix::operator++(int) {
    CMatrix C = *this;
//    CMatrix&& m = std::move(CMatrix(nR, nC, MI_VALUE, 1.0));
    add(CMatrix(nR, nC, MI_VALUE, 1.0));
    return C;
}

CMatrix CMatrix::operator--() {
//    CMatrix&& m = std::move(CMatrix(nR, nC, MI_VALUE, -1.0));
    add(CMatrix(nR, nC, MI_VALUE, -1.0));
    return *this;
}

CMatrix CMatrix::operator--(int) {
    CMatrix r = *this;
//    CMatrix&& m = std::move(CMatrix(nR, nC, MI_VALUE, -1.0));
    add(CMatrix(nR, nC, MI_VALUE, -1.0));
    return r;
}

CMatrix CMatrix::operator-() {
    for (int iR = 0; iR < nR; iR++)
        for (int iC = 0; iC < nC; iC++)
            values[iR][iC] = -values[iR][iC];
    return *this;
}

CMatrix CMatrix::operator+() {
    return *this;
}

void CMatrix::setSubMatrix(int r, int c, const CMatrix &m) {
    if ((r + m.nR) > nR || (c + m.nC) > nC)throw ("Invalid matrix dimension");
    for (int iR = 0; iR < m.nR; iR++)
        for (int iC = 0; iC < m.nC; iC++)
            values[r + iR][c + iC] = m.values[iR][iC];
}

CMatrix CMatrix::getSubMatrix(int r, int c, int nr, int nc) {
    if ((r + nr) > nR || (c + nc) > nC)throw ("Invalid matrix dimension");
    CMatrix m(nr, nc);
    for (int iR = 0; iR < m.nR; iR++)
        for (int iC = 0; iC < m.nC; iC++)
            m.values[iR][iC] = values[r + iR][c + iC];
    return m;
}

void CMatrix::addColumn(const CMatrix &m) {
    CMatrix n(std::max(nR, m.nR), nC + m.nC);
    n.setSubMatrix(0, 0, *this);
    n.setSubMatrix(0, nC, m);
    *this = n;
}

void CMatrix::addRow(const CMatrix &m) {
    CMatrix n(nR + m.nR, std::max(nC, m.nC));
    n.setSubMatrix(0, 0, *this);
    n.setSubMatrix(nR, 0, m);
    *this = n;
}

CMatrix CMatrix::getCofactor(int r, int c) {
    if (nR <= 1 && nC <= 1)throw ("Invalid matrix dimension");
    CMatrix m(nR - 1, nC - 1);
    for (int iR = 0; iR < m.nR; iR++)
        for (int iC = 0; iC < m.nC; iC++) {
            int sR = (iR < r) ? iR : iR + 1;
            int sC = (iC < c) ? iC : iC + 1;
            m.values[iR][iC] = values[sR][sC];
        }
    return m;
}

double CMatrix::getDeterminant() {
    if (nR != nC)throw ("Invalid matrix dimension");
    if (nR == 1 && nC == 1)return values[0][0];
    double value = 0, m = 1;
    for (int iR = 0; iR < nR; iR++) {
        value += m * values[0][iR] * getCofactor(0, iR).getDeterminant();
        m *= -1;
    }
    return value;
}

CMatrix CMatrix::getTranspose() {
    CMatrix r(nC,nR);
    for (int iR = 0; iR < r.nR; iR++)
    {
        for (int iC = 0; iC < r.nC; iC++)
        {
            r.values[iR][iC] = values[iC][iR];
        }
    }

    return r;
}

std::istream &operator>>(std::istream &is, CMatrix &m) {
    std::string s;
    getline(is, s, ']');
    s+="]";
    m = CMatrix(s);
    return is;
}

std::ostream&operator<<(std::ostream &os,CMatrix &m) {
    os << m.getString();
    return os;
}
