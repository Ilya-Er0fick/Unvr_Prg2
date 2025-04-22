#include <iostream>
#include "StackArray.h"
#include "getPostfixFromInfix.hpp"


int main() {
    try {
        StackArray<std::size_t> stack(3);

        stack.push(1);
        stack.push(2);
        stack.push(3);

        while (!stack.isEmpty()) {
            std::cout << stack.pop() << " ";
        }
    }
    catch (const WrongStackSize& ex)
    {
        std::cout << ex.getMessage() << std::endl;
    }
    catch (const StackOverflow& ex)
    {
        std::cout << ex.getMessage() << std::endl;
    }
    catch (const StackUnderflow& ex)
    {
        std::cout << ex.getMessage() << std::endl;
    }

    try {
        std::string infix = "1+2+3+4+5";
        std::string postfix = InfixToPostfix::convert(infix);
        double result = InfixToPostfix::evaluatePostfix(postfix);
        std::cout << "\n";
        std::cout << "Infix: " << infix << "\n";
        std::cout << "Postfix: " << postfix << "\n";
        std::cout << "Reuslt: " << result << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}