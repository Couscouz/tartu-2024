/**
 * \file Point2.cpp
 * \brief Methods of the class Point2.
 *
 * This file contains all the methods definitions of the class Point2.
 */

#ifndef POINT2_H
#define POINT2_H

#include <iostream> /**< ostream needed */
using std::ostream; /**< ostream usage */

/**
 * \brief Class representing a 2D point.
 *
 * This class represents a point in 2D space defined by its X and Y coordinates.
 * It provides methods for basic operations such as calculating the distance between two points
 * and overloading the output stream operator for convenient output.
 */
class Point2 {

    public:
        float x = 0; /**< The X coordinate of the 2D point */
        float y = 0; /**< The Y coordinate of the 2D point */

        Point2() = default; /**< Default constructor */
        Point2(float nx, float ny); /**< Constructor with all parameters */

        /**
         * \brief Gets the distance with another 2D point.
         *
         * This public method returns the distance with another 2D point v.
         * 
         * \param v The point p (Point2)
         * \return The distance (float) with the v point
         */
        float distanceFrom(Point2 v);
        
        /**
         * \brief Overloads the output stream operator for the Point2 class.
         *
         * This function overloads the output stream operator to enable
         * the display of a Point2 object on an output stream such as std::cout.
         * 
         * \param os The output stream (std::ostream&)
         * \param v The point to display (const Point2)
         * \return A reference to the output stream to allow chaining operations
         */
        friend ostream& operator << (ostream& os, Point2 v);
};

#endif 
