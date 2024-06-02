/**
 * \file line3.h
 * \brief Header file of the class Line3.
 *
 * This file contains all definitions of the class Line3.
 */

#ifndef LINE3_H
#define LINE3_H

#include "point3.h" /**< Needed in class definition and some methods */
#include <iostream> /**< ostream needed */
using std::ostream; /**< ostream usage */


/**
 * \brief Class representing a 3D line.
 *
 * This class represents a 3D line defined by two end points (p1 and p2).
 * It provides methods for basic operations such as calculating the length of the line
 * and overloading the output stream operator for convenient output.
 */
class Line3 {

    public: 
        Point3 p1; /**< The first end point of the 3D line */
        Point3 p2; /**< The first end point of the 3D line */

        Line3() = default; /**< Default constructor */
        Line3(Point3 np1, Point3 np2); /**< Constructor with all parameters */

        /**
         * \brief Overloads the output stream operator for the Line3 class.
         *
         * This function overloads the output stream operator to enable
         * the display of a Line3 object on an output stream such as std::cout.
         * 
         * \param o The output stream (std::ostream&)
         * \param l The line to display (const Line3&)
         * \return A reference to the output stream to allow chaining operations
         */ 
        friend ostream& operator<<(ostream& o, const Line3& l);

        /**
         * \brief Gets the length of a line.
         *
         * This public method returns the distance between the 2 3D point of the line.
         * 
         * \return The length (float) of the line
         */
        float length ();
};



#endif
