#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define PRINT_RESULT(message) std::cout << message << std::endl

float min(float a, float b) {
    return (a < b) ? a : b;
}

float max(float a, float b) {
    return (a > b) ? a : b;
}

int main(int argc, char *argv[]) {
    //args check
    if (argc != 4) {
        printf("Usage: %s <number1> <number2> <operation>\n", argv[0]);
        return 1;
    }

    //args retrieve
    float num1 = atof(argv[1]);
    float num2 = atof(argv[2]);
    const char *operation = argv[3];

    if (strcmp(operation, "min") == 0) {
        PRINT_RESULT(min(num1,num2));
    } else if (strcmp(operation, "max") == 0) {
        PRINT_RESULT(max(num1,num2));
    } else {
        PRINT_RESULT("Error: Operation not valid");
    }

    return 0;
}