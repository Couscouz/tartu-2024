/**
 * \file test.cpp
 * \brief Test file of the program.
 *
 * This file contains all the unit tests of the functions.
 */

#include <iostream> /* Input and output */
#include <cstdlib>  /* EXIT_SUCCESS and other constants */
#include "functions.h" /* Our own features */

using namespace std; /* Elements from std namespace */

int test_passed = 0; /**< Number of tests performed */
int test_successful = 0; /**< Number of tests successful */

/**
 * \brief TEST method if for unit tests.
 *
 * This macro is used to perform a test and prints whether it passed or failed.
 */
#define TEST(ex) cout << "Test " << ++test_passed << ". " << #ex << " " << ((ex) ? (++test_successful, "OK") :"FAIL") << endl


/**
 * \brief Main testing function.
 *
 * This is the entry point of the test program.
 * Print result of each test
 * 
 * \return 0 on successful execution.
 */
int main() {
    cout << "--Testing all functions--" << endl;

    // Test function minimum results
    TEST(minimum(35, 40) == 35);
    TEST(minimum(35, 40) != 40);

    // Test function maximum results
    TEST(maximum(65, 40) == 65);
    TEST(maximum(65, 40) != 40);

    // Test function product results
    TEST(product(20, 15) == 300);
    TEST(product(20, 15) != 0);

    // Test function power results
    TEST(power(17, 4) == 83521);
    TEST(power(17, 9) != 0);
    TEST(power(9, 0) == 1);
    TEST(power(14, 0) != 0);

    //Test function gcd result
    TEST(gcd(15, 4) == 1);
    TEST(gcd(20, 78) == 2);
    TEST(gcd(3, 7) != 0);
    TEST(gcd(4, 8) != 2);

    //Conclusion with final count
    cout << "Result: " << test_successful << "/" << test_passed << endl; 

    return EXIT_SUCCESS;
}
