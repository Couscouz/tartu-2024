/**
 * \file line2.h
 * \brief Header file of the class Line2.
 *
 * This file contains all definitions of the class Line2.
 */

#ifndef LINE2_H
#define LINE2_H

#include "point2.h" /**< Needed in class definition and some methods */
#include <iostream> /**< ostream needed */
using std::ostream; /**< ostream usage */


/**
 * \brief Class representing a 2D line.
 *
 * This class represents a 2D line defined by two end points (p1 and p2).
 * It provides methods for basic operations such as calculating the length of the line
 * and overloading the output stream operator for convenient output.
 */
class Line2 {

    public: 
        Point2 p1; /**< The first end point of the line */
        Point2 p2; /**< The second end of point the line */

        Line2() = default; /**< Default constructor */
        Line2(Point2 np1, Point2 np2); /**< Constructor with all parameters */

        /**
         * \brief Overloads the output stream operator for the Line2 class.
         *
         * This function overloads the output stream operator to enable
         * the display of a Line2 object on an output stream such as std::cout.
         * 
         * \param o The output stream (std::ostream&)
         * \param l The line to display (const Line2&)
         * \return A reference to the output stream to allow chaining operations
         */
        friend ostream& operator<<(ostream& o, const Line2& l);

        /**
         * \brief Gets the length of a line.
         *
         * This public method returns the distance between the 2 2D point of the line.
         * 
         * \return The length (float) of the line
         */
        float length ();
};

#endif