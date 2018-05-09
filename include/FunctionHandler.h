#ifndef FUNCTIONHANDLER_H
#define FUNCTIONHANDLER_H

#include <map>
#include <string>
#include "Function.h"

class FunctionHandler
{
    public:
        FunctionHandler(std::map<std::string, Function>&);
};

#endif // FUNCTIONHANDLER_H
