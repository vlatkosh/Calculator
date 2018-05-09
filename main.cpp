#include <iostream>
#include <ios>
#include <iomanip>
#include <Calculator.h>
using namespace std;

/// Driver program I guess?

int main()
{
    Calculator calc;
    cout << setprecision(16);
    while (1) {
        string input;
        getline(cin, input);
        if (input == "functions") {
            cout << calc.getFunctions() << "\n";
        }
        else if (input == "constants") {
            cout << calc.getConstants() << "\n";
        }
        else if (input == "operators") {
            cout << calc.getOperators() << "\n";
        }
        else {
            cout << "= " << calc.parse(input) << "\n\n";
        }
    }
}
