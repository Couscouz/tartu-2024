/**
 * \file point3.h
 * \brief Header file of the class Point3.
 *
 * This file contains all definitions of the class Point3.
 */

#ifndef POINT3_H
#define POINT3_H

#include <iostream> /**< ostream needed */
using std::ostream; /**< ostream usage */


/**
 * \brief Class representing a 3D point.
 *
 * This class represents a point in 3D space defined by its X and Y coordinates.
 * It provides methods for basic operations such as calculating the distance between two points
 * and overloading the output stream operator for convenient output.
 */
class Point3 {

    public: 
        float x = 0; /**< The X coordinate of the 3D point */
        float y = 0; /**< The Y coordinate of the 3D point */
        float z = 0; /**< The Z coordinate of the 3D point */

        Point3() = default; /**< Default constructor */
        Point3(float nx, float ny, float nz); /**< Constructor with all parameters */

        /**
         * \brief Overloads the output stream operator for the Point3 class.
         *
         * This function overloads the output stream operator to enable
         * the display of a Point3 object on an output stream such as std::cout.
         * 
         * \param o The output stream (std::ostream&)
         * \param p The point to display (const Point3&)
         * \return A reference to the output stream to allow chaining operations
         */
        friend ostream& operator<<(ostream& o, const Point3& p);
        
        /**
         * \brief Gets the distance with another 3D point.
         *
         * This public method returns the distance with another 3D point p.
         * 
         * \param p The point p (Point3)
         * \return The distance (float) with the p point
         */
        float distanceFrom (Point3 p);
};

#endif
