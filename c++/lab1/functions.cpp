/**
 * \file functions.cpp
 * \brief Functions file of the program.
 *
 * This file contains all the function definitions of our program.
 */

#include "functions.h" /* Header file - Our own features */
#include <cmath> /* pow() needed */
#include <climits> /* Infinite check */

long minimum (long a, long b) { 
    if (a > b) 
        return b; 
    else 
        return a; 
}

long maximum (long a, long b) { 
    if (a > b) 
        return a; 
    else 
        return b; 
}

long product (long a, long b) { 
    return a*b; 
}

long power (long a, long b) {
    long long result = pow(a,b);
    //if the result is a fraction or infinity (more than long limit)
    //for example, for some negative power, output zero
    if (a == 0 || b < 0 || result == LLONG_MAX || result == LLONG_MIN) {
        result = 0;
    }
    return result; 
}

long gcd (long a, long b) {
    long r =0;
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}