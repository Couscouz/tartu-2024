/**
 * \file circle2.h
 * \brief Header file of the class Circle2.
 *
 * This file contains all definitions of the class Circle2.
 */

#ifndef CIRCLE2_H
#define CIRCLE2_H


#include "point2.h" /**< Needed in class definition and some methods */
#include "line2.h" /**< Needed in some methods */
#include <iostream> /**< ostream needed */
using std::ostream; /**< ostream usage */


/**
 * \brief Class representing a 2D circle.
 *
 * This class represents a 2D circle defined by a center point (p1) and a radius (r).
 * It provides methods for basic operations such as scaling, calculating circumference and area,
 * and checking if points or lines are contained within the circle.
 */
class Circle2 {

    public: 
        Point2 p1; /**< The center of the 2D circle */
        float r = 1; /**< The radius of the 2D circle (cant be negative) */

        Circle2() = default; /**< Default constructor */
        Circle2(Point2 np1, float nr); /**< Constructor with all parameters */

        /**
         * \brief Overloads the output stream operator for the Circle2 class.
         *
         * This function overloads the output stream operator to enable
         * the display of a Circle2 object on an output stream such as std::cout.
         * 
         * \param o The output stream (std::ostream&)
         * \param c The circle to display (const Circle2&)
         * \return A reference to the output stream to allow chaining operations
         */
        friend ostream& operator<<(ostream& o, const Circle2& c);

        /**
         * \brief Scale a 2D circle by a factor.
         *
         * This public method change the radius of the 2D circle by applying a factor to it
         * If this result in a negative radius, the new radius will be 0
         * 
         * \param factor The factor (float) used to scale the 2D circle
         */
        void scale (float factor);
        
        /**
         * \brief Gets the circumference of a 2D circle.
         *
         * This public method returns the circumference of the 2D circle.
         * 
         * \return circumference (float) of the circle
         */
        float circumference ();

        /**
         * \brief Gets the area of a 2D circle.
         *
         * This public method returns the area of the 2D circle.
         * 
         * \return area (float) of the circle
         */
        float area ();

        /**
         * \brief Check if a 2D poit is fully included in a 2D circle.
         *
         * This public method returns true if the 2D point is in (or on) the 2D circle
         * and false if not
         * 
         * \param p The 2D poit (Point2)
         * \return boolean of the point in the circle
         */
        bool contains (Point2 p);

        /**
         * \brief Check if a 2D line is fully included in a 2D circle.
         *
         * This public method returns true if both of the 2D points of the line are in (or on) the 2D circle
         * and false if at least one is not
         * 
         * \param l The 2D line (Line2)
         * \return boolean of the line in the circle
         */
        bool contains (Line2 l);
};

#endif
