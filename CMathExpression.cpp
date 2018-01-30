//
// Created by abyss on 1/26/18.
//

#include "CMathExpression.h"

CMathExpression::CMathExpression() {

}

CMathExpression::CMathExpression(std::string) {

}

bool CMathExpression::isWhiteSpace(const char c) {
    return (' ' == c) || ('\n' == c) ||
           ('\r' == c) || ('\t' == c) ||
           ('\b' == c) || ('\v' == c) ||
           ('\f' == c);
}

bool CMathExpression::isOperator(const char c) {
    return ('+' == c) || ('-' == c) ||
           ('*' == c) || ('/' == c) ||
           ('^' == c) || ('<' == c) ||
           ('>' == c) || ('=' == c) ||
           (',' == c) || ('!' == c) ||
           ('(' == c) || (')' == c) ||
           ('[' == c) || (']' == c) ||
           ('{' == c) || ('}' == c) ||
           ('%' == c) || (':' == c) ||
           ('?' == c) || ('&' == c) ||
           ('|' == c) || (';' == c);
}

bool CMathExpression::isLetter(const char c) {
    return (('a' <= c) && (c <= 'z')) ||
           (('A' <= c) && (c <= 'Z'));
}

bool CMathExpression::isDigit(const char c) {
    return ('0' <= c) && (c <= '9');
}

bool CMathExpression::isLetterOrDigit(const char c) {
    return isLetter(c) || isDigit(c);
}

bool CMathExpression::isLeftBracket(const char c) {
    return ('(' == c);
}

bool CMathExpression::isLeftSquareBracket(const char c) {
    return ('[' == c);
}

bool CMathExpression::isRightBracket(const char c) {
    return (')' == c);
}

bool CMathExpression::isRightSquareBracket(const char c) {
    return (']' == c);
}

bool CMathExpression::isSign(const char c) {
    return ('+' == c) || ('-' == c);
}

bool CMathExpression::isInvalid(const char c) {
    return !isWhiteSpace(c) &&
           !isOperator(c) &&
           !isLetter(c) &&
           !isdigit(c) &&
           ('.' != c) &&
           ('_' != c) &&
           ('$' != c) &&
           ('~' != c) &&
           ('\'' != c);
}

