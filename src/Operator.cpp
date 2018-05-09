#include "Operator.h"

#define TTOperator 3

Operator::Operator()
{

}

Operator::Operator(std::string symbol, int precedence, char associativity)
{
    this->token.type = TTOperator;
    this->token.symbol = symbol;
    this->token.precedence = precedence;
    this->token.associativity = associativity;
}
