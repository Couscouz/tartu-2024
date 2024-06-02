/**
 * \file point.h
 * \brief Header file of the class Point<n>.
 *
 * This file contains all definitions of the class Point<n>.
 */

#ifndef POINT_H
#define POINT_H


#include <iostream> /**< ostream needed */
#include <string> /**< string needed */
#include <sstream> /**< ostream needed */
#include <list> /**< list needed */
#include <cmath> /**< sqrt() and pow() needed */

using namespace std; /* Elements from std namespace */

/**
 * \brief Class representing a N-dimensionnal Point.
 *
 * This class represents a n-dim point defined by a list of floats
 * It provides methods for basic operations such as calculating distanceFrom another Point<n>,
 * overloading the output stream operator for convenient output.
 */
template <unsigned short n>
class Point {

    public: 
        list<float> coords; /**< The n coordinates defining the point */

        /**< Default constructor */
        Point() {
            //Assign 0 to each coordinate of the Point
            for (unsigned short i=0; i<n; i++){
                coords.push_back(0.0);
            }
        }
        
        /**< Constructor with all parameters */
        Point(list<float> crds) {
            //Check if given dimensions correspond to Point dimension n
            if (crds.size() != n) {
                cerr << "Error: Number of given coordinates does not match the dimension of the point." << endl;
                return;
            }
            coords = crds;
        }

        /**
         * \brief Overloads the output stream operator for the Point<n> class.
         *
         * This function overloads the output stream operator to enable
         * the display of a Point<n> object on an output stream such as std::cout.
         * 
         * \param o The output stream (std::ostream&)
         * \param p The line to display (const Point<n>&)
         * \return A reference to the output stream to allow chaining operations
         */
        friend ostream& operator<<(ostream& o, const Point<n>& p) {
            o << p.toString();
            return o;
        }

        /**
         * \brief Create string of the Point content.
         *
         * This function create a string of the point, formated like :
         * (x1, x2, ....., xn)
         * 
         * \return A string of the point definition
         */
        string toString() const {
            string result = "(";
            stringstream temp; /*In order to print float without tons of 0*/
            auto it = coords.begin();

            while (it != coords.end()) {
                temp.str("");
                temp << *it;
                result += temp.str();
                ++it;
                if (it != coords.end()) 
                    result += ", ";
            }

            result += ")";
            return result;
        }

        /**
         * \brief Gets the distance with another n-dim point.
         *
         * This public method returns the distance with another 2D point p.
         * 
         * \param v The point v (Point<n>)
         * \return The distance (float) with the v point
         */
        float distanceFrom(Point<n> v){
            //Check if distance is possible
            if (coords.size() != v.coords.size()) {
                cerr << "Error: Dimension of the 2 points does not match." << endl;
                return -1;
            }

            float total = 0.0;
            auto it1 = coords.begin();
            auto it2 = v.coords.begin();

            for (; it1 != coords.end(); ++it1, ++it2) {
                total += pow(*it1 - *it2, 2);
            }
            return (sqrt(total));
        }
};

#endif
