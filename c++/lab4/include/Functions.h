/**
 * \file Functions.h
 * \brief Header file of all our Functions.
 *
 * This file contains all functions defitions.
 */

#ifndef SOLVEEQUATION_H
#define SOLVEEQUATION_H

/**
 * \brief Swap the value of 2 variables.
 *
 * This public method swap the value of 2 variables.
 * \param a The 1st variable (T&)
 * \param b The 2nd variable (T&)
 */
template<class T> 
void swap_ref (T &a, T &b) {
	T temp = a;
    a = b;
    b = temp;
}

/**
 * \brief Swap the adresses of 2 variables.
 *
 * This public method swap the adresses of 2 variables.
 * \param a The 1st variable (T*)
 * \param b The 2nd variable (T*)
 */
template<class T> 
void swap_ptr (T *a, T *b) {
	T temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * \brief Solve 1st and 2nd degree equations.
 *
 * This public functions solve 1st and 2nd degree equations.
 * 
 * \param a The 2nd degree factor (double)
 * \param b The 1st degree stream (double)
 * \param c The constant (double)
 * \param x1 The adress of the 1st solution (double&)
 * \param x2 The adress of the 2nd solution (double&)
 * \return boolean depending of the solvability of the equation
 */
bool solve (double a, double b, double c, double &x1, double &x2);

#endif
