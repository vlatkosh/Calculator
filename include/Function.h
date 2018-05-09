#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <functional>
#include <vector>
#include "Token.h"

class Function
{
    public:
        Function();
        Function(std::string, int);
        Function(std::string, std::string, int);

        std::string description;

        Token token;
        int numParameters;
        std::function<long double(std::vector<long double>&)> method;
};

#endif // FUNCTION_H
