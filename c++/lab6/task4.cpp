
#include <iostream>
#include <stdexcept>


int string_to_int(const char* string) {
    int output;
    try {
        output = std::stoi(string);
        if (output < 1 || output > 99) {
            std::cerr << "invalid input" << std::endl;
            throw;
        }
    } catch (const std::invalid_argument&) {
        std::cerr << "invalid input" << std::endl;
        throw;
    }
    return output;
}

int main(int argc, char *argv[]) {
    //args check
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    //args retrieve
    const char *input = argv[1];
    int output = string_to_int(input);
    if (output != -1)
        std::cout << "Number is " << output << std::endl;

    int result;
    //Valid input
    std::cout << "=====Valid input tests=====" << std::endl; 
    std::cout << "1 is valid: " << string_to_int("1") << std::endl;
    std::cout << "50 is valid: " << string_to_int("50") << std::endl;
    std::cout << "99 is valid: " << string_to_int("99") << std::endl;

    //Invalid input
    std::cout << "=====Invalid input tests=====" << std::endl; 
    std::cout << "0 is: " << string_to_int("0") << std::endl;
    std::cout << "100 is: " << string_to_int("100") << std::endl;
    std::cout << "-1 is: " << string_to_int("-1") << std::endl;
    std::cout << "-50 is: " << string_to_int("-50") << std::endl;
    try {
        std::cout << "\"abc\" is valid: " << string_to_int("abc") << std::endl;
    } catch(const std::invalid_argument&) {
        std::cout << "not valid atoi()" << std::endl;
    }
    
    //Edge cases
    std::cout << "=====nEdge cases tests=====" << std::endl;
    std::cout << "Close to lower boundary 1: " << string_to_int("1") << std::endl;
    std::cout << "Close to lower boundary 2: " << string_to_int("2") << std::endl;
    std::cout << "Close to lower boundary 98: " << string_to_int("98") << std::endl;
    std::cout << "Close to lower boundary 99: " << string_to_int("99") << std::endl;

    return 0;
}