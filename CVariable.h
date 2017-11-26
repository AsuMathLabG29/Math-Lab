//
// Created by abyss on 11/26/17.
//

#ifndef MATH_LAB_CVARIABLE_H
#define MATH_LAB_CVARIABLE_H


#include <iostream>
#include <vector>
#include "CMatrix.h"


class CVariable
{
private:
    char* name;
    CMatrix value; //value is now a CMatrix
public:
    CVariable(const char* init_name);
    CVariable(const char* init_name, double init_value);
    CVariable(const char* init_name, CMatrix init_value);
    CVariable(const CVariable &copy);
    const char* getName() const;
    std::string getString();
    virtual CMatrix& operator*();
    virtual CMatrix operator*() const;
    virtual CMatrix& operator=(double newValue);
    virtual CVariable& operator=(const CVariable& newValue);
    virtual void print();
    virtual ~CVariable();
    friend std::ostream& operator<<(std::ostream& out, CVariable& cvar);
};

class CVarDB
{
    friend std::ostream& operator<<(std::ostream& out, CVarDB& cdb);
private:
    std::vector<CVariable> db;
public:
    CVarDB();
    bool add(CVariable& newVar);
    CVariable* search(const char* name);
    bool isThere(const char* name);
    virtual void print();
    ~CVarDB();
};


#endif //MATH_LAB_CVARIABLE_H
