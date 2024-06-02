/**
 * \file line.h
 * \brief Header file of the class Polygon<T>.
 *
 * This file contains all definitions of the class Line<T>.
 */

#ifndef LINE_H
#define LINE_H

#include <iostream> /**< ostream needed */
#include <string> /**< string needed in toString */

using namespace std; /* Elements from std namespace */

/**
 * \brief Class representing a Line between Point<n>
 *
 * This class represents a line defined by two N-dimensionnals end points (p1 and p2).
 * It provides methods for basic operations such as calculating the length of the line
 * and overloading the output stream operator for convenient output.
 */
template <class T>
class Line {

    public: 
        T p1;  /**< The first end point (Point<n>) of the line */
        T p2; /**< The second end point (Point<n>) of the line */

        /**< Default constructor */
        Line() {
            p1 = T();
            p2 = T();
        }
        
        /**< Constructor with parameters */
        Line(T np1, T np2) {
            p1 = np1;
            p2 = np2;
        }

        /**
         * \brief Overloads the output stream operator for the Line<T> class.
         *
         * This function overloads the output stream operator to enable
         * the display of a Line<T> object on an output stream such as std::cout.
         * 
         * \param o The output stream (std::ostream&)
         * \param l The line to display (const Line<T>&)
         * \return A reference to the output stream to allow chaining operations
         */
        friend ostream& operator<<(ostream& o, const Line<T>& l) {
            o << l.toString();
            return o;
        }

        /**
         * \brief Create string of the Line content.
         *
         * This function create a string of the line, formated like :
         * (Point1-Point2)
         * 
         * \return A string of the line definition
         */
        string toString() const {
            return ("(" + p1.toString() + "-" + p2.toString() + ")");
        }

        /**
         * \brief Gets the length of a n-dim line.
         *
         * This public method returns the distance between the 2 n-dim points defining the line.
         * 
         * \return The length (float) of the n-dim line
         */
        float length() {
            return p1.distanceFrom(p2);
        }
};

#endif
