#include <iostream>
#include <string>

bool isValidPizzaCount(int count) {
    return (count >= 1 && count <= 99);
}



int main() {
    // Valid input
    std::cout << "=====Valid input tests=====" << std::endl; 
    std::cout << "1 is valid: " << isValidPizzaCount(1) << std::endl;
    std::cout << "50 is valid: " << isValidPizzaCount(50) << std::endl;
    std::cout << "99 is valid: " << isValidPizzaCount(99) << std::endl;

    // Invalid input
    std::cout << "=====Invalid input tests=====" << std::endl; 
    std::cout << "0 is valid: " << isValidPizzaCount(0) << std::endl;
    std::cout << "100 is valid: " << isValidPizzaCount(100) << std::endl;
    std::cout << "-1 is valid: " << isValidPizzaCount(-1) << std::endl;
    std::cout << "-50 is valid: " << isValidPizzaCount(-50) << std::endl;
    try {
        std::cout << "\"abc\" is valid: " << isValidPizzaCount(std::stoi("abc")) << std::endl;
    } catch(const std::invalid_argument&) {
        std::cout << "not valid atoi()" << std::endl;
    }
    
    // Edge cases
    std::cout << "=====nEdge cases tests=====" << std::endl;
    std::cout << "Close to lower boundary 1: " << isValidPizzaCount(1) << std::endl;
    std::cout << "Close to lower boundary 2: " << isValidPizzaCount(2) << std::endl;
    std::cout << "Close to upper boundary 98: " << isValidPizzaCount(98) << std::endl;
    std::cout << "Close to upper boundary 99: " << isValidPizzaCount(99) << std::endl;

    return 0;
}