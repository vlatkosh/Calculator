#include "ConstantHandler.h"

ConstantHandler::ConstantHandler(std::map<std::string, long double> &m) {
    m["pi"] = 3.14159265358979323846;
    m["e"] = 2.71828182845904523536;
    m["fi"] = 1.61803398875;
    m["g"] = 9.81;
    m["c"] = 299792458;
}
