#ifndef OPERATORHANDLER_H
#define OPERATORHANDLER_H

#include "Operator.h"
#include <map>
#include <string>

class OperatorHandler
{
    public:
        OperatorHandler(std::map<std::string, Operator>&);
};

#endif // OPERATORHANDLER_H
