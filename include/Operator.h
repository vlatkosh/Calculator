#ifndef OPERATOR_H
#define OPERATOR_H

#include "Token.h"
#include <functional>

class Operator
{
    public:
        Operator();
        Operator(std::string, int, char);

        Token token;
        std::function<long double(long double, long double)> method;
};

#endif // OPERATOR_H
