#include "FunctionHandler.h"

#include <utility>
#include <cmath>

typedef long double ld;
typedef std::vector<ld> vv;

FunctionHandler::FunctionHandler(std::map<std::string, Function> &m) {

    m.insert(std::make_pair("sqrt", Function("sqrt(x); square root", "sqrt", 1)));
    m["sqrt"].method = [](vv &v) -> ld { return std::sqrt(v[0]); };

    m.insert(std::make_pair("exp", Function("exp(x); exponential function", "exp", 1)));
    m["exp"].method = [](vv &v) -> ld { return std::exp(v[0]); };

    m.insert(std::make_pair("pow", Function("pow(base, power); Power", "pow", 2)));
    m["pow"].method = [](vv &v) -> ld { return std::pow(v[0], v[1]); };

    m.insert(std::make_pair("fact", Function("fact(x); factorial function", "fact", 1)));
    m["fact"].method = [](vv &v) -> ld { return std::tgamma(v[0]+1); };

    m.insert(std::make_pair("mod", Function("mod(a, b); compute a modulo b", "mod", 2)));
    m["mod"].method = [](vv &v) -> ld { return (ld)((int)v[0] % (int)v[1]); };

    //trigonometric
    m.insert(std::make_pair("sin", Function("sin(x); sine", "sin", 1)));
    m["sin"].method = [](vv &v) -> ld { return std::sin(v[0]); };

    m.insert(std::make_pair("cos", Function("cos(x); cosine", "cos", 1)));
    m["cos"].method = [](vv &v) -> ld { return std::cos(v[0]); };

    m.insert(std::make_pair("tan", Function("tan(x); tangent", "tan", 1)));
    m["tan"].method = [](vv &v) -> ld { return std::tan(v[0]); };

    m.insert(std::make_pair("asin", Function("asin", 1)));
    m["asin"].method = [](vv &v) -> ld { return std::asin(v[0]); };

    m.insert(std::make_pair("acos", Function("acos", 1)));
    m["acos"].method = [](vv &v) -> ld { return std::acos(v[0]); };

    m.insert(std::make_pair("atan", Function("atan", 1)));
    m["atan"].method = [](vv &v) -> ld { return std::atan(v[0]); };

    //hyperbolic trigonometric?
    m.insert(std::make_pair("sinh", Function("sinh", 1)));
    m["sinh"].method = [](vv &v) -> ld { return std::sinh(v[0]); };

    m.insert(std::make_pair("cosh", Function("cosh", 1)));
    m["cosh"].method = [](vv &v) -> ld { return std::cosh(v[0]); };

    m.insert(std::make_pair("tanh", Function("tanh", 1)));
    m["tanh"].method = [](vv &v) -> ld { return std::tanh(v[0]); };

    m.insert(std::make_pair("asinh", Function("asinh", 1)));
    m["asinh"].method = [](vv &v) -> ld { return std::asinh(v[0]); };

    m.insert(std::make_pair("acosh", Function("acosh", 1)));
    m["acosh"].method = [](vv &v) -> ld { return std::acosh(v[0]); };

    m.insert(std::make_pair("atanh", Function("atanh", 1)));
    m["atanh"].method = [](vv &v) -> ld { return std::atanh(v[0]); };


}
