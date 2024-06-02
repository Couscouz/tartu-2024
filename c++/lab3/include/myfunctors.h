/**
 * \file myfunctors.h
 * \brief Header file of the class SumElements<T>.
 *
 * This file contains all definitions of the class SumElements<T>.
 */

#ifndef MYFUNCTORS_H
#define MYFUNCTORS_H

#include <iostream> /**< ostream needed */
#include <string> /**< string needed */
#include <sstream> /**< stringstream needed */
#include <vector> /**< vectors needed */

using namespace std; /* Elements from std namespace */

/**
 * \brief Class representing a N-dimensionnal Point.
 *
 * This class represents a n-dim point defined by a list of floats
 * It provides methods for basic operations such as calculating distanceFrom another Point<n>,
 * overloading the output stream operator for convenient output.
 */
template <class T>
class SumElements {

    public: 
        T sum; /**< The current sum of the object */

        /**< Default constructor */
        SumElements() {
            sum = T();
        }
        
        /**< Constructor with parameters */
        SumElements(vector<T>& values) {
            //Check if type is correct
            if (!(is_same<T, int>::value || is_same<T, float>::value || is_same<T, string>::value)) {
                throw invalid_argument("T must be int, float, or std::string");
            }
            
            //Adding values
            auto it = values.begin();
            for(; it != values.end(); ++it) {
                sum += it;
            }
        }

        /**< The operator in order to edit our sum */
        void operator()(const T value){
            sum += value; // Add the value to the sum
        }

        /**< Retrieve the sum of the object */
        T result() const {
            return sum;
        }
        
};

#endif
