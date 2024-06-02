/**
 * \file sphere.h
 * \brief Header file of the class Sphere<T>.
 *
 * This file contains all definitions of the class Sphere<T>.
 */

#ifndef SPHERE_H
#define SPHERE_H


#include <iostream> /**< ostream needed */
#include <string> /**< string needed in toString */
#include <sstream> /* Needed to pretty print floats */

using namespace std; /* Elements from std namespace */

/**
 * \brief Class representing a Sphere around a Point<n>
 *
 * This class represents a sphere defined by a N-dimensionnals center point (o) and a floating radius r (r>=0).
 * It provides methods for basic operations such as calculating if a Line or a Point is in the Sphere, scaling it
 * and overloading the output stream operator for convenient output.
 */
template <class T>
class Sphere {

    public: 
        T o; /**< The center point (Point<n>) of the n-dim sphere */
        float r; /**< The radius (float) defining the n-dim sphere */

        /**< Default constructor */
        Sphere() {
            o = T();
            r = 0;
        }
        
        /**< Constructor with parameters */
        Sphere(T no, float nr) {
            o = no;
            if (nr < 0) {
                throw invalid_argument("radius of Sphere<T> must be positive or null");
            } else {
                r = nr;
            }
        }

        /**
         * \brief Overloads the output stream operator for the Sphere<T> class.
         *
         * This function overloads the output stream operator to enable
         * the display of a Sphere<T> object on an output stream such as std::cout.
         * 
         * \param o The output stream (std::ostream&)
         * \param s The line to display (const Sphere<T>&)
         * \return A reference to the output stream to allow chaining operations
         */
        friend ostream& operator<<(ostream& o, const Sphere<T>& s) {
            o << s.toString();
            return o;
        }

        /**
         * \brief Create string of the Sphere content.
         *
         * This function create a string of the sphere, formated like :
         * (Point, r)
         * 
         * \return A string of the sphere definition
         */
        string toString() const {
            stringstream radius; /*In order to print float without useless 0*/
            radius << r;
            return ("(" + o.toString() + ", " + radius.str() + ")");
        }

        /**
         * \brief Check if a n-dim point is fully included in a n-dim sphere.
         *
         * This public method returns true if the Point<n> is in (or on) the sphere
         * and false if not
         * 
         * \param v The n-dim point v (Point<n>)
         * \return boolean of the point in the sphere
         */
        float contains(T v) {
            return (o.distanceFrom(v) <= r);
        }

        /**
         * \brief Check if a n-dim line is fully included in a n-dim sphere.
         *
         * This public method returns true if both of the n-dim points of the line are in (or on) the sphere
         * and false if at least one is not
         * 
         * \param l The n-dim line l (Line<T>)
         * \return boolean of the line in the sphere
         */
        float contains(Line<T> l) {
            return (contains(l.p1) && contains(l.p2));
        }

        /**
         * \brief Scale a n-dim sphere by a factor.
         *
         * This public method change the radius of the n-dim sphere by applying a factor to it
         * If the factor is negative, the radius is not modified
         * 
         * \param factor The factor factor (float)
         */
        void scale(float factor) {
            if (factor >= 0)
                r = factor*r;
        }
};

#endif
