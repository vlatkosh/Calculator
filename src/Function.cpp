#include "Function.h"

#define TTFunction 2

Function::Function()
{

}

Function::Function(std::string symbol, int numParameters)
{
    this->token.type = TTFunction;
    this->token.symbol = symbol;

    this->description = "";
    this->numParameters = numParameters;
}


Function::Function(std::string description, std::string symbol, int numParameters)
{
    this->token.type = TTFunction;
    this->token.symbol = symbol;

    this->description = description;
    this->numParameters = numParameters;
}
