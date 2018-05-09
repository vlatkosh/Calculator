#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Token.h"
#include "Operator.h"
#include "Function.h"
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <sstream>

class Calculator
{
    public:
        Calculator();
        std::string getOperators();
        std::string getConstants();
        std::string getFunctions();
        long double parse(std::string);

    private:
        std::vector<Token> tokens;
        std::queue<Token> outputQueue; //postfix
        std::stack<Token> operatorStack;

        std::map<std::string, Operator> operators;
        std::map<std::string, Function> functions;
        std::map<std::string, long double> constants;

        void reset();

        bool searchNumber(const std::string&, int&);
        int searchString(const std::string&, const std::string&, int);
        bool searchOperator(const std::string&, int&);
        bool searchFunction(const std::string&, int&);
        bool searchConstant(const std::string&, int&);
        void evaluateTokens(const std::string&);

        void parseTokens();
        long double evaluatePostfixOutput();

        struct CException;
        std::stringstream candyStream;
};

#endif // CALCULATOR_H
