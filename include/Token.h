#ifndef TOKEN_H
#define TOKEN_H

#include <string>

class Token
{
    public:
        Token();
        Token(int);
        Token(long double);
        Token(int, long double);
        Token(int, std::string, int, char);

        int type;

        long double value;

        std::string symbol;
        int precedence;
        char associativity;
};

#endif // TOKEN_H
