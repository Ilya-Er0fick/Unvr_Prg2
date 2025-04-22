#ifndef INFIX_TO_POSTFIX_HPP
#define INFIX_TO_POSTFIX_HPP

#include <string>
#include <stdexcept>

class InfixToPostfix {
public:
    static std::string convert(const std::string& infix);
    static double evaluatePostfix(const std::string& postfix);

private:
    static bool isOperator(char c);
    static int getPriority(char op);
    static void validateExpression(const std::string& infix);
    static bool isUnaryOperator(char c, const std::string& expr, size_t pos);
};

#endif