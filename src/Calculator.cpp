#include "Calculator.h"
#include "OperatorHandler.h"
#include "ConstantHandler.h"
#include "FunctionHandler.h"
#include <iostream>
#include <ios>
#include <iomanip>
#include <algorithm>

#define TTNumber 1
#define TTFunction 2
#define TTOperator 3
#define TTLeftBracket 4
#define TTRightBracket 5

using std::cout;

/**
    TODO:
        MAKE pow(2, -5) WORK
**/


/// Init, misc
///

//courtesy of https://stackoverflow.com/questions/8152720/correct-way-to-inherit-from-stdexception
class Exception: public std::exception {
    public:
        explicit Exception(const char* message): msg_(message) {}
        explicit Exception(const std::string& message): msg_(message) {}
        virtual ~Exception() throw() {}
        virtual const char* what() const throw () {
            return msg_.c_str();
        }
    protected:
        std::string msg_;
};

Calculator::Calculator() {
    OperatorHandler operatorhandler(operators);
    ConstantHandler constanthandler(constants);
    FunctionHandler functionhandler(functions);
    candyStream << std::setprecision(16);
}

void Calculator::reset() {
    tokens.clear();
    while (!outputQueue.empty())
        outputQueue.pop();
    while (!operatorStack.empty())
        operatorStack.pop();
}

inline bool isDigit(char ch) {
    return '0' <= ch && ch <= '9';
}

/// Candy
///

std::string Calculator::getConstants() {
    candyStream.str("");
    for (auto it = constants.begin(); it != constants.end(); ++it) {
        candyStream << "  " << it->first << " = " << it->second << "\n";
    }
    return candyStream.str();
}

std::string Calculator::getFunctions() {
    candyStream.str("");
    for (auto it = functions.begin(); it != functions.end(); ++it) {
        if (it->second.description == "") {
            candyStream << "  " << it->second.token.symbol << "\n";
        }
        else {
            candyStream << "  " << it->second.description << "\n";
        }
    }
    return candyStream.str();
}

std::string Calculator::getOperators() {
    candyStream.str("");
    for (auto it = operators.begin(); it != operators.end(); ++it) {
        candyStream << "  " << it->first;
    }
    return candyStream.str();
}

/// Token evaluation (input string -> tokens)
///

bool Calculator::searchNumber(const std::string &input, int &i) {
    if (!isDigit(input[i]))
        return false;

    std::string number_str = "";
    while (i < (signed)input.length() && (isDigit(input[i]) || input[i] == '.')) {
        number_str += input[i];
        ++i;
    }
    --i;
    long double number = std::stod(number_str);
    tokens.push_back(Token(number));
    return true;
}

int Calculator::searchString(const std::string &input, const std::string &target, int i) {
    if (input[i] != target[0])
        return false;

    int j, k; //j is new i
    std::string temp = "";
    for (j = i, k = 0;
         j < (signed)input.length() && k < (signed)target.length() && target[k] == input[j];
         ++j) {
        temp += target[k];
        ++k;
    }
    return temp == target ? j : i;
}

bool Calculator::searchConstant(const std::string &input, int &i) {
    //It will prioritize constants like 'pizza' over 'pi'
    int best_new_i = i;
    long double best_constant = 0.0;
    for (auto it = constants.begin(); it != constants.end(); ++it) {
        int new_i = searchString(input, it->first, i);
        if (new_i > best_new_i) {
            best_new_i = new_i;
            best_constant = it->second;
        }
    }
    if (best_new_i > i) {
        i = best_new_i-1; //decrement by one because best_new_i is AT LEAST i+1 (it is the first index after the found string)
        tokens.push_back(Token(best_constant));
        return true;
    }
    return false;
}

bool Calculator::searchOperator(const std::string &input, int &i) {
    //It will prioritize operators like '**' (commonly exponentiation) over '*'
    int best_new_i = i;
    Token bestFoundToken;
    for (auto it = operators.begin(); it != operators.end(); ++it) {
        Operator op = it->second;
        int new_i = searchString(input, op.token.symbol, i);
        if (new_i > best_new_i) {
            best_new_i = new_i;
            bestFoundToken = op.token;
        }
    }
    if (best_new_i > i) {
        i = best_new_i-1;
        tokens.push_back(bestFoundToken);
        return true;
    }
    return false;
}

bool Calculator::searchFunction(const std::string &input, int &i) {
    //It will prioritize functions like 'longFunction' over 'longFun'
    int best_new_i = i;
    Token bestFoundToken;
    for (auto it = functions.begin(); it != functions.end(); ++it) {
        Function f = it->second;
        int new_i = searchString(input, f.token.symbol, i);
        if (new_i > best_new_i) {
            best_new_i = new_i;
            bestFoundToken = f.token;
        }
    }
    if (best_new_i > i) {
        i = best_new_i-1;
        tokens.push_back(bestFoundToken);
        return true;
    }
    return false;
}

void Calculator::evaluateTokens(const std::string &input) {
    for (int i = 0; i < (signed)input.length(); ++i) {
        //The order of the following checks matters
        if (input[i] == '(') {
            tokens.push_back(Token(TTLeftBracket));
        }
        else if (input[i] == ')') {
            tokens.push_back(Token(TTRightBracket));
        }
        else if (searchNumber(input, i)) {
            //pass
        }
        else if (searchOperator(input, i)) {
            //pass
        }
        else if (searchFunction(input, i)) {
            //pass
        }
        else if (searchConstant(input, i)) {
            //pass
        }
    }
}

/// Token parsing (tokens -> postfix output queue)
///

void Calculator::parseTokens() {
    /*
    this function was written using pseudocode from
    https://en.wikipedia.org/wiki/Shunting-yard_algorithm#The_algorithm_in_detail
    */
    for (Token token : tokens) {
        switch (token.type) {
            case TTNumber:
                outputQueue.push(token);
                break;
            case TTFunction:
                //We do not need to use Wall Notation or Count Notation
                //for the number of parameters, because we have it in the token itself
                operatorStack.push(token);
                break;
            case TTOperator:
                while (!operatorStack.empty()
                      && (operatorStack.top().type != TTLeftBracket)
                      && (operatorStack.top().type == TTFunction
                         || operatorStack.top().precedence < token.precedence //actually higher precedence
                         || (operatorStack.top().precedence == token.precedence &&
                             operatorStack.top().associativity == 'l') ) ) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(token);
                break;
            case TTLeftBracket:
                operatorStack.push(token);
                break;
            case TTRightBracket:
                while (operatorStack.top().type != TTLeftBracket) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.pop(); //pop the left bracket from the stack
                /* if the stack runs out without finding a left bracket,
                   then there are mismatched parentheses. */
                break;
            default:
                throw Exception("Unknown token type");
        }
    }
    while (!operatorStack.empty()) {
        /* if the operator token on the top of the stack is a bracket,
           then there are mismatched parentheses. */
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
    }
}

/// Output parsing (postfix output queue -> number result)
///

long double Calculator::evaluatePostfixOutput() {
    /*
    this function was written using pseudocode from
    https://en.wikipedia.org/wiki/Reverse_Polish_notation
    */
    std::stack<long double> staqq;
    cout << "postfix { ";
    while (!outputQueue.empty()) {
        Token token = outputQueue.front();
        outputQueue.pop();
        if (token.type == TTNumber) {
            staqq.push(token.value);
            cout << token.value << " ";
        }
        else if (token.type == TTFunction) {
            cout << token.symbol << " ";
            int numParameters = functions[token.symbol].numParameters;
            if (staqq.size() < (unsigned)numParameters) {
                throw Exception("Too few arguments for function " + token.symbol);
            }
            std::vector<long double> arguments;
            while (numParameters--) {
                arguments.push_back(staqq.top());
                staqq.pop();
            }
            std::reverse(arguments.begin(), arguments.end()); //That's just how the cookie crumbles.
            long double result = functions[token.symbol].method(arguments);
            staqq.push(result);
        }
        else {
            cout << token.symbol << " ";
            long double o1, o2;
            if (staqq.size() == 0) {
                throw Exception("Operator " + token.symbol + " may be missing operands left or right?");
            }
            else if (staqq.size() == 1) {
                o2 = staqq.top();
                o1 = 0;
            }
            else {
                o2 = staqq.top();
                staqq.pop();
                o1 = staqq.top();
                staqq.pop();
            }
            long double result = operators[token.symbol].method(o1, o2);
            staqq.push(result);
        }
    }
    cout << "}\n";
    long double result = staqq.top();
    staqq.pop();
    return result;
}

/// Input parsing
///

long double Calculator::parse(std::string input) {
    reset();

    try {
        evaluateTokens(input);
    } catch (Exception e) { cout << "{{evaluateTokens error: " << e.what() << " }}\n"; }

    try {
        parseTokens();
    } catch (Exception e) { cout << "{{parseTokens error: " << e.what() << " }}\n"; }

    long double result = 0.0;
    try {
        result = evaluatePostfixOutput();
    } catch (Exception e) { cout << "{{evaluatePostfixOutput error: " << e.what() << " }}\n"; }

    return result;
}
