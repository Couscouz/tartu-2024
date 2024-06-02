/**
 * \file Functions.cpp
 * \brief All our functions defined in Functions header file.
 *
 * This file contains all the functions definitions .
 */

#include "Functions.h" /**< Our class definition */
#include <math.h> /**< sqrt() needed */

bool solve (double a, double b, double c, double &x1, double &x2) {

    
    if (a == 0) {
        //if equation is bx+c=0
        x1 = -c / b;
        x2 = -c / b;
    } else {
        double delta = b*b - 4*a*c;

        if (delta > 0) {
            x1 = (-b + sqrt(delta)) / (2*a);
            x2 = (-b - sqrt(delta)) / (2*a);
        } else if (delta == 0) {
            x1 = -b / (2*a);
            x2 = -b / (2*a);
        } else {
            return false;
        }
    }
	
	return true;
}
