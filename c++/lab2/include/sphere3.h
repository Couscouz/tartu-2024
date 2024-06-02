/**
 * \file sphere3.h
 * \brief Header file of the class Sphere3.
 *
 * This file contains all definitions of the class Sphere3.
 */

#ifndef SPHERE3_H
#define SPHERE3_H

#include "point3.h" /**< Needed in class definition and some methods */
#include "line3.h" /**< Needed in some methods */
#include <iostream> /**< ostream needed */
using std::ostream; /**< ostream usage */


/**
 * \brief Class representing a 3D sphere.
 *
 * This class represents a 3D sphere defined by a center point (p1) and a radius (r).
 * It provides methods for basic operations such as scaling, calculating circumference, area, volume,
 * and checking if points or lines are contained within the sphere.
 */
class Sphere3 {

    public: 
        Point3 p1; /**< The center of the 3D sphere */
        float r = 1; /**< The radius of the 3D sphere (cant be negative) */

        Sphere3() = default; /**< Default constructor */
        Sphere3(Point3 np1, float nr); /**< Constructor with all parameters */

        /**
         * \brief Overloads the output stream operator for the Sphere3 class.
         *
         * This function overloads the output stream operator to enable
         * the display of a Sphere3 object on an output stream such as std::cout.
         * 
         * \param o The output stream (std::ostream&)
         * \param s The sphere to display (const Sphere3&)
         * \return A reference to the output stream to allow chaining operations
         */
        friend ostream& operator<<(ostream& o, const Sphere3& s);
        
        /**
         * \brief Scale a 3D sphere by a factor.
         *
         * This public method change the radius of the 3D sphere by applying a factor to it
         * If this result in a negative radius, the new radius will be 0
         * 
         * \param factor The factor (float) used to scale the 3D sphere
         */
        void scale (float factor);
        
        /**
         * \brief Gets the circumference of a 3D sphere.
         *
         * This public method returns the circumference of the 3D sphere.
         * 
         * \return circumference (float) of the sphere
         */
        float circumference ();

        /**
         * \brief Gets the area of a 3D sphere.
         *
         * This public method returns the area of the 3D sphere.
         * 
         * \return area (float) of the sphere
         */
        float area ();

        /**
         * \brief Gets the volume of a 3D sphere.
         *
         * This public method returns the volume of the 3D spehre.
         * 
         * \return volume (float) of the sphere
         */
        float volume ();

        /**
         * \brief Check if a 3D point is fully included in a 3D sphere.
         *
         * This public method returns true if both of the 3D points of the line are in (or on) the 3D sphere
         * and false if at least one is not
         * 
         * \param p The 3D point (Point3)
         * \return boolean of the point in the sphere
         */
        bool contains (Point3 p);

        /**
         * \brief Check if a 3D line is fully included in a 3D sphere.
         *
         * This public method returns true if both of the 3D points of the line are in (or on) the 3D sphere
         * and false if at least one is not
         * 
         * \param l The 3D line (Line3)
         * \return boolean of the line in the sphere
         */
        bool contains (Line3 l);
};


#endif
