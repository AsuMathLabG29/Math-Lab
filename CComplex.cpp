//
// Created by abyss on 1/27/18.
//

#include "CComplex.h"
#include "math.h"
#define PI 3.14159265359

CComplex::CComplex()
{
    R = 0;
    I = 0;
}

CComplex::CComplex(double R, double I) {
    this->R = R;
    this->I = I;
}

CComplex::CComplex(CComplex &C) {
    copy(C);
}

void CComplex::copy(CComplex &C) {
    this->R = C.R;
    this->I = C.I;
}

std::string CComplex::getString() {
    char text[100];
    if (I == 0) sprintf(text,"%g",R);
    else if (R == 0) sprintf(text, "%g i", I);
    else if (I > 0) sprintf(text, "%g + %g i", R, I);
    else sprintf(text, "%g - %g i", R, -I);
    return std::string(text);
}

double CComplex::magnitude() {
    double mag = 0;
    mag = sqrt((R*R + I*I));
    return mag;
}

double CComplex::angle()
{
    return atan2(I,R);
}

void CComplex::negative()
{
    R *= -1;
    I *= -1;
}

double CComplex::real() {
    return this->R;
}

double CComplex::imaginary() {
    return this->I;
}

CComplex CComplex::addComplex(CComplex &A,const CComplex &B) {
    CComplex C;
    C.R = A.R + B.R;
    C.I = A.I + B.I;
    return C;
}

void CComplex::add(CComplex& C) {
    R += C.R;
    I += C.I;
}

CComplex& CComplex::operator=(CComplex &C)
{
    copy(C);
    return *this;
}

CComplex CComplex::operator=(double D)
{
    return CComplex(D,0);
}

void CComplex::operator+=(CComplex &C)
{
    add(C);
}

void CComplex::operator+=(double D)
{
    R += D;
}

CComplex CComplex::operator+(CComplex & C)
{
    return addComplex(*this,C);
}

CComplex CComplex::operator+(double D)
{

    return addComplex(*this, CComplex(D,0));
}

CComplex CComplex::operator-()
{
    return CComplex(-R,-I);
}

CComplex operator*(CComplex& A, CComplex& B){
    double R = A.real()*B.real() - A.imaginary()*B.imaginary();
    double I = A.real()*B.imaginary() + A.imaginary()*B.real();
    return CComplex(R, I);
}

CComplex::operator const string()
{
    return getString();
}

CComplex CComplex::operator++()
{
    R++;
    return *this;
}
CComplex CComplex::operator++(int)
{
    CComplex C = *this;
    R+=1;
    return C;
}
double CComplex::operator[](string name)
{
    if(name=="magnitude")return magnitude();
    if(name=="angle")return angle();
    if(name=="real")return real();
    if(name=="imaginary")return imaginary();
    return 0.0;
}
double CComplex::operator()(string name, string info)
{
    if(name=="angle")
    {
        if(info=="degree")return angle()*180.0/PI;
        if(info=="radian" || info.length()==0)return angle();
    }
    return (*this)[name];
}

CComplex::~CComplex()
{

}

std::istream & operator>>(std::istream & is, CComplex & C)
{
    is >> C.R;
    is >> C.I;
    return is;
}

std::ostream & operator<<(std::ostream & os, CComplex & C)
{
    os << C.getString();
    return os;
}
