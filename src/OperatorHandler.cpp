#include "OperatorHandler.h"

#include <utility>
#include <cmath>

typedef long double ld;

OperatorHandler::OperatorHandler(std::map<std::string, Operator> &m) {

    m.insert(std::make_pair("**", Operator("**", 2, 'r')));
    m["**"].method = [](ld a, ld b) -> ld {
        return (ld)pow(a, b);
    };

    m.insert(std::make_pair("*", Operator("*", 3, 'r'))); //or r
    m["*"].method = [](ld a, ld b) -> ld {return a * b;};

    m.insert(std::make_pair("/", Operator("/", 3, 'l')));
    m["/"].method = [](ld a, ld b) -> ld {return a / b;};

    m.insert(std::make_pair("%", Operator("%", 3, 'l')));
    m["%"].method = [](ld a, ld b) -> ld {
        return (ld)((int)a % (int)b);
    };

    m.insert(std::make_pair("+", Operator("+", 4, 'r'))); //or r
    m["+"].method = [](ld a, ld b) -> ld {return a + b;};

    m.insert(std::make_pair("-", Operator("-", 4, 'l')));
    m["-"].method= [](ld a, ld b) -> ld {return a - b;};

}
