/**
 * \file main.cpp
 * \brief Main file of the program.
 *
 * This file contains the main function where the program execution starts.
 */

#include <iostream> /* Input and output */
#include <fstream> /* File input and output */
#include <sstream> /* String stream */
#include <cstdlib>  /* EXIT_SUCCESS and other constants */
#include "functions.h" /* Our own features */

using namespace std; /* Elements from std namespace */

/**
 * \brief Main function.
 *
 * This is the entry point of the program.
 *
 * \param argc The number of command-line arguments.
 * \param argv An array containing the command-line arguments.
 * \return 0 on successful execution.
 */
int main(int argc, char *argv[]) {
    
    if (argc == 2) {
        
        fstream inputFile; /* File stream for input */
        string content; /* String to store the file content */

        inputFile.open (argv[1]); /* Open the file specified in 1st argument */
        
        //Storing the 2 integers from arguments
        long a = 0;
        long b = 0;

        //Checking if file exist and is correctly opened
        if (inputFile.is_open())
        {
            //reading the 1st line of the file
            getline(inputFile,content);
            //and parsing it to get the 2 integers
            istringstream iss(content);
            iss >> a >> b;      

            //Print template
            cout << a << " " << b << endl;
            cout << minimum(a,b) <<endl;
            cout << maximum(a,b) << endl;
            cout << product(a,b) << endl;
            cout << power(a,b) << endl;
            cout << gcd(a,b) << endl;
        }
        else
        {
            cout << "Error opening file";
        }
        inputFile.close();

    } else if (argc == 3) {
        //Storing the 2 integers from arguments
        long a = atoi(argv[1]);
        long b = atoi(argv[2]);

        //Print template
        cout << a << " " << b << endl;
        cout << minimum(a,b) <<endl;
        cout << maximum(a,b) << endl;
        cout << product(a,b) << endl;
        cout << power(a,b) << endl;
        cout << gcd(a,b) << endl;

    } else if (argc == 4) {

        //last argument should be function name
        string functionName = argv[3];
        
        //Storing the 2 integers from arguments
        long a = atoi(argv[1]);
        long b = atoi(argv[2]);

        //Print template - 1st lie
        cout << a << " " << b << endl;

        //Print template according to function name
        if (functionName.compare("minimum") == 0) {
            cout << minimum(a,b) << endl;
        } else if (functionName.compare("maximum") == 0) {
            cout << maximum(a,b) << endl;
        } else if (functionName.compare("product") == 0) {
            cout << product(a,b) << endl;
        } else if (functionName.compare("power") == 0) {
            cout << power(a,b) << endl;
        } else if (functionName.compare("gcd") == 0) {
            cout << gcd(a,b) << endl;
        } else {
            cout << "Function name not recognized" << endl;
        }

    } else {
        //if there isnt 1, 2 or 3 arguments, exiting error
        cout << "Error: Wrong input format" << endl;
        cout << "Need to have between 1 and 3 arguments" << endl;
    }
    return EXIT_SUCCESS;
}
