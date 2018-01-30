//
// Created by abyss on 1/26/18.
//

#ifndef MATH_LAB_CMATHEXPRESSION_H
#define MATH_LAB_CMATHEXPRESSION_H

#include "CMatrix.h"
#include "cstring"

class CMathExpression {
    static const std::string arithmaticOps[] = {"+", "-", "*", "/", "^"};
    static const size_t arithmaticOpsSize = sizeof(arithmaticOps) / sizeof(std::string);
    static const std::string assignmentOps[] = {"+=", "-=", "*=", "/=", "="};
    static const size_t assignmentOpsSize = sizeof(assignmentOps) / sizeof(std::string);
    static const std::string functionList[] = {"abs", "abs", "acos", "asin", "atan",
                                               "atan2", "cos", "cot", "log", "ln", "sin", "sqrt", "tan"};
    static const size_t functionListSize = sizeof(functionList) / sizeof(std::string);
public:
    CMathExpression();

    CMathExpression(std::string);


    bool isLetter(const char c);

    bool isDigit(const char c);

    bool isLetterOrDigit(const char c);

    bool isOperator(const char c);

    bool isWhiteSpace(const char c);

    bool isSign(const char c);

    bool isLeftBracket(const char c);

    bool isLeftSquareBracket(const char c);

    bool isRightBracket(const char c);

    bool isRightSquareBracket(const char c);

    bool isInvalid(const char c);

    bool isMatrix(std::string);

    bool isComplex(std::string);


    ~CMathExpression();
};


#endif //MATH_LAB_CMATHEXPRESSION_H
