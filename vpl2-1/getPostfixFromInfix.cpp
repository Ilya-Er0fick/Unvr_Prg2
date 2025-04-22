#include "getPostfixFromInfix.hpp"
#include "StackArray.h"
#include <map>
#include <sstream>
#include <cmath>
#include <cctype>

std::string InfixToPostfix::convert(const std::string& infix) {
    validateExpression(infix);

    StackArray<char> operators(infix.size());
    std::string postfix;
    std::string currentNumber;
    std::map<char, int> priorities = {
        {'+', 1}, {'-', 1},
        {'*', 2}, {'/', 2},
        {'^', 3}, {'~', 4}
    };

    for (size_t i = 0; i < infix.size(); ++i) {
        char c = infix[i];
        if (isspace(c)) {
            if (!currentNumber.empty()) {
                postfix += currentNumber + " ";
                currentNumber.clear();
            }
            continue;
        }

        if (isdigit(c) || c == '.' || ((c == '-' || c == '+') && isUnaryOperator(c, infix, i))) {
            currentNumber += c;
            continue;
        }

        if (!currentNumber.empty()) {
            postfix += currentNumber + " ";
            currentNumber.clear();
        }

        if (c == '(') {
            operators.push(c);
        }
        else if (c == ')') {
            while (!operators.isEmpty() && operators.peek() != '(') {
                postfix += std::string(1, operators.pop()) + " ";
            }
            if (operators.isEmpty()) {
                throw std::runtime_error("Unbalanced parentheses");
            }
            operators.pop();
        }
        else if (isOperator(c)) {
            if (c == '-' && isUnaryOperator(c, infix, i)) {
                c = '~';
            }
            while (!operators.isEmpty() && operators.peek() != '(' &&
                   priorities[operators.peek()] >= priorities[c]) {
                postfix += std::string(1, operators.pop()) + " ";
            }
            operators.push(c);
        }
    }

    if (!currentNumber.empty()) {
        postfix += currentNumber + " ";
    }

    while (!operators.isEmpty()) {
        if (operators.peek() == '(') {
            throw std::runtime_error("Unbalanced parentheses");
        }
        postfix += std::string(1, operators.pop()) + " ";
    }

    if (!postfix.empty() && postfix.back() == ' ') {
        postfix.pop_back();
    }

    return postfix;
}

double InfixToPostfix::evaluatePostfix(const std::string& postfix) {
    StackArray<double> operands(postfix.size()/2 + 1);
    std::istringstream iss(postfix);
    std::string token;

    while (iss >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            operands.push(std::stod(token));
        } else {
            if (token == "~") {
                if (operands.isEmpty()) {
                    throw std::runtime_error("Not enough operands");
                }
                double a = operands.pop();
                operands.push(-a);
            } else {
                if (operands.getSize() < 2) {
                    throw std::runtime_error("Not enough operands for operator " + token);
                }
                double b = operands.pop();
                double a = operands.pop();

                switch (token[0]) {
                    case '+': operands.push(a + b); break;
                    case '-': operands.push(a - b); break;
                    case '*': operands.push(a * b); break;
                    case '/':
                        if (b == 0) throw std::runtime_error("Division by zero");
                        operands.push(a / b);
                        break;
                    case '^': operands.push(std::pow(a, b)); break;
                    default:
                        throw std::runtime_error("Unknown operator: " + token);
                }
            }
        }
    }

    if (operands.getSize() != 1) {
        throw std::runtime_error("Invalid expression");
    }
    return operands.pop();
}

bool InfixToPostfix::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '~';
}

int InfixToPostfix::getPriority(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        case '~': return 4;
        default: return 0;
    }
}

bool InfixToPostfix::isUnaryOperator(char c, const std::string& expr, size_t pos) {
    if (c != '-' && c != '+') return false;
    return pos == 0 || expr[pos-1] == '(' || isOperator(expr[pos-1]);
}

void InfixToPostfix::validateExpression(const std::string& infix) {
    int balance = 0;
    for (char c : infix) {
        if (c == '(') balance++;
        else if (c == ')') balance--;
        if (balance < 0) {
            throw std::runtime_error("Unbalanced parentheses");
        }
    }
    if (balance != 0) {
        throw std::runtime_error("Unbalanced parentheses");
    }
}