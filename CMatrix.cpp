//
// Created by abyss on 10/26/17.
//

#include "CMatrix.h"
#include <cstdarg>
#include <algorithm>
#include "sstream"
#include "iomanip"

#define EPS 1e-10

CMatrix::CMatrix() {
    nR = nC = 0;
    values = NULL;
    name = 'a';
}

CMatrix::CMatrix(char name) {
    this->name = name;
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

void CMatrix::setName(char name) {
    this->name = name;
}

char CMatrix::getName() {
    return this->name;
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

void CMatrix::copy(double &d) {
    reset();
    this->nR = 1;
    this->nC = 1;
    values = new double *[1];
    values[0] = new double[1];
    values[0][0] = d;
}

void CMatrix::copy(std::string &s) {
    reset();
    char *buffer = new char[s.length() + 1];
    strcpy(buffer, s.c_str());
    char *lineContext;
    const char *lineSeparators = ";\r\n";
    char *line = strtok_r(buffer, lineSeparators, &lineContext);
    while (line) {
        CMatrix row;
        char *context;
        const char *separators = " []";
        char *token = strtok_r(line, separators, &context);
        while (token) {
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
    std::ostringstream os;
    os.precision(5);
    os << std::fixed;
    for (int iR = 0; iR < nR; iR++) {
        os << "    ";
        for (int iC = 0; iC < nC; iC++) {
            int pos = os.tellp();
            if (values[iR][iC] < 0) { os.seekp(pos - 1); }
            os << values[iR][iC] << "    ";
        }
        os << std::endl;
    }
    return os.str();
}

CMatrix &CMatrix::operator=(const CMatrix &m) {
    copy(m);
    return *this;
}

CMatrix &CMatrix::operator=(double &d) {
    copy(d);
    return *this;
}

CMatrix &CMatrix::operator=(const char *s) {
    std::string c(s);
    copy(c);
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

CMatrix CMatrix::operator*(double &d) {
    CMatrix r = *this;
    r *= d;
    return r;
}

void CMatrix::div(const CMatrix &m) {
    if (nR != m.nR || nC != m.nC)
        throw ("Invalid matrix dimension");
    CMatrix r(nR, nC);
    CMatrix a = m;
    try {
        r = *this * a.getInverse();
    } catch (const char *msg) {
        try {
            a = *this;
            r = a.getInverse() * m;
        } catch (const char *msg) {
            throw("No unique solution");
        }

    }
    copy(r);
}

void CMatrix::operator/=(const CMatrix &m) {
    div(m);
}

void CMatrix::operator/=(double d) {
    if (d == 0) throw ("Error: division by zero");
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


CMatrix &CMatrix::operator++() {
    add(CMatrix(nR, nC, MI_VALUE, 1.0));
    return *this;
}

CMatrix CMatrix::operator++(int) {
    CMatrix C = *this;
    add(CMatrix(nR, nC, MI_VALUE, 1.0));
    return C;
}

CMatrix &CMatrix::operator--() {
    add(CMatrix(nR, nC, MI_VALUE, -1.0));
    return *this;
}

CMatrix CMatrix::operator--(int) {
    CMatrix r = *this;
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

const CMatrix CMatrix::getCofactorMatrix(int r, int c) const {
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

CMatrix CMatrix::getTranspose() {
    CMatrix r(nC, nR);
    for (int iR = 0; iR < r.nR; iR++) {
        for (int iC = 0; iC < r.nC; iC++) {
            r.values[iR][iC] = values[iC][iR];
        }
    }

    return r;
}

std::istream &operator>>(std::istream &is, CMatrix &m) {
    std::string s;
    getline(is, s, ']');
    s += "]";
    m = CMatrix(s);
    return is;
}

std::ostream &operator<<(std::ostream &os, CMatrix &m) {
    os << m.getString();
    return os;
}

double det(CMatrix &m) {
    if (m.nR != m.nC)throw ("Invalid matrix dimension");
    if (m.nR == 1 && m.nC == 1)return m.values[0][0];
    double det = 1;
    CMatrix c = m.gaussianEliminate();
    for (int i = 0; i < m.nR; ++i) {

        det *= c.values[i][i];

    }
    return det;
}

CMatrix CMatrix::getInverse() {
    if (det(*this) == 0) throw ("Determinant equal 0, the matrix is not invertible");
    CMatrix I(nC, nR, MI_EYE);
    CMatrix AI = CMatrix::augment(*this, I);
    CMatrix U = AI.gaussianEliminate();
    CMatrix IAInverse = U.rowReduceFromGaussian();
    CMatrix AInverse(nC, nR);
    for (int i = 0; i < AInverse.nR; ++i) {
        for (int j = 0; j < AInverse.nC; ++j) {
            AInverse(i, j) = IAInverse(i, j + nC);
        }
    }
    return AInverse;
}

CMatrix CMatrix::augment(CMatrix &A, CMatrix &B) {
    CMatrix AB(A.nR, A.nC + B.nC);
    for (int i = 0; i < AB.nR; ++i) {
        for (int j = 0; j < AB.nC; ++j) {
            if (j < A.nC)
                AB(i, j) = A(i, j);
            else
                AB(i, j) = B(i, j - B.nC);
        }
    }
    return AB;
}

CMatrix CMatrix::gaussianEliminate() {
    CMatrix Ab(*this);
    int rows = Ab.nR;
    int cols = Ab.nC;
    int aCols = cols - 1;

    int i = 0;
    int j = 0;

    while (i < rows) {
        // find a pivot for the row
        bool pivot_found = false;
        while (j < aCols && !pivot_found) {
            if (Ab(i, j) != 0) { // pivot not equal to 0
                pivot_found = true;
            } else { // check for a possible swap
                int max_row = i;
                double max_val = 0;
                for (int k = i + 1; k < rows; ++k) {
                    double cur_abs = Ab(k, j) >= 0 ? Ab(k, j) : -1 * Ab(k, j);
                    if (cur_abs > max_val) {
                        max_row = k;
                        max_val = cur_abs;
                    }
                }
                if (max_row != i) {
                    Ab.swapRows(max_row, i);
                    pivot_found = true;
                } else {
                    j++;
                }
            }
        }

        // perform elimination as normal if pivot was found
        if (pivot_found) {
            for (int t = i + 1; t < rows; ++t) {
                for (int s = j + 1; s < cols; ++s) {
                    Ab(t, s) = Ab(t, s) - Ab(i, s) * (Ab(t, j) / Ab(i, j));
                    if (Ab(t, s) < EPS && Ab(t, s) > -1 * EPS)
                        Ab(t, s) = 0;
                }
                Ab(t, j) = 0;
            }
        }

        i++;
        j++;
    }

    return Ab;
}

void CMatrix::swapRows(int r1, int r2) {
    double *temp = values[r1];
    values[r1] = values[r2];
    values[r2] = temp;
}

CMatrix CMatrix::rowReduceFromGaussian() {
    CMatrix R(*this);
    int rows = R.nR;
    int cols = R.nC;

    int i = rows - 1; // row tracker
    int j = cols - 2; // column tracker

    // iterate through every row
    while (i >= 0) {
        // find the pivot column
        int k = j - 1;
        while (k >= 0) {
            if (R(i, k) != 0)
                j = k;
            k--;
        }

        // zero out elements above pivots if pivot not 0
        if (R(i, j) != 0) {

            for (int t = i - 1; t >= 0; --t) {
                for (int s = 0; s < cols; ++s) {
                    if (s != j) {
                        R(t, s) = R(t, s) - R(i, s) * (R(t, j) / R(i, j));
                        if (R(t, s) < EPS && R(t, s) > -1 * EPS)
                            R(t, s) = 0;
                    }
                }
                R(t, j) = 0;
            }

            // divide row by pivot
            for (int l = j + 1; l < cols; ++l) {
                R(i, l) = R(i, l) / R(i, j);
                if (R(i, l) < EPS && R(i, l) > -1 * EPS)
                    R(i, l) = 0;
            }
            R(i, j) = 1;

        }

        i--;
        j--;
    }

    return R;
}

CMatrix operator/(double d, CMatrix &m) {
    CMatrix r(m.getnR(), m.getnC());
    for (int iR = 0; iR < m.getnR(); iR++)
        for (int iC = 0; iC < m.getnC(); iC++) {
            if (m(iR, iC) == 0) throw ("Error: division by zero");
            r(iR, iC) = d / m(iR, iC);
        }
    return r;
}

CMatrix operator*(double d, CMatrix &m) {
    CMatrix r(m.getnR(), m.getnC());
    for (int iR = 0; iR < m.getnR(); iR++)
        for (int iC = 0; iC < m.getnC(); iC++) {
            r(iR, iC) = d * m(iR, iC);
        }
    return r;
}

CMatrix operator+(double d, CMatrix &m) {
    CMatrix r(m.getnR(), m.getnC());
    for (int iR = 0; iR < m.getnR(); iR++)
        for (int iC = 0; iC < m.getnC(); iC++) {
            r(iR, iC) = d + m(iR, iC);
        }
    return r;
}

CMatrix operator-(double d, CMatrix &m) {
    CMatrix r(m.getnR(), m.getnC());
    for (int iR = 0; iR < m.getnR(); iR++)
        for (int iC = 0; iC < m.getnC(); iC++) {
            r(iR, iC) = d - m(iR, iC);
        }
    return r;
}
