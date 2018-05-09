#include "Token.h"

#define TTNumber 1
#define TTFunction 2
#define TTOperator 3
#define TTLeftBracket 4
#define TTRightBracket 5

Token::Token() {

}

Token::Token(int type) {
    this->type = type;
}

Token::Token(long double value) {
    this->type = TTNumber;
    this->value = value;
}

Token::Token(int type, long double value) {
    this->type = type;
    this->value = value;
}

Token::Token(int type, std::string symbol, int precedence, char associativity) {
    this->type = type;
    this->symbol = symbol;
    this->precedence = precedence;
    this->associativity = associativity;
}
