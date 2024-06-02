/**
 * \file polygon.h
 * \brief Header file of the class Polygon<T,n>.
 *
 * This file contains all definitions of the class Sphere<T,n>.
 */

#ifndef POLYGON_H
#define POLYGON_H


#include <iostream> /**< ostream needed */
#include <string> /**< string needed */
#include <sstream> /**< stringstream needed */
#include <vector> /**< vectors needed */

using namespace std; /* Elements from std namespace */

/**
 * \brief Class representing a N-dimensionnal Polygon.
 *
 * This class represents a n-dim polygon defined by a vector<T> of Point<n>
 * It provides methods for basic operations such as calculating perimeter,
 * and overloading the output stream operator for convenient output.
 */
template <class T, unsigned short n>
class Polygon {

    public: 
        vector<T> points; /**< The vector of n-dim points defining the polygon */

        /**< Default constructor */
        Polygon() {
            for (unsigned short i=0; i<n; ++i) {
                points.push_back(T());
            }
        }
        
        /**< Constructor with parameters */
        Polygon(vector<T> pts) {
            points = pts;
        }

        /**
         * \brief Overloads the output stream operator for the Polygon<T,n> class.
         *
         * This function overloads the output stream operator to enable
         * the display of a Polygon<T,n> object on an output stream such as std::cout.
         * 
         * \param o The output stream (std::ostream&)
         * \param p The line to display (const Polygon<T,n>&)
         * \return A reference to the output stream to allow chaining operations
         */
        friend ostream& operator<<(ostream& o, const Polygon<T,n>& p) {
            o << p.toString();
            return o;
        }

        /**
         * \brief Create string of the Polygon content.
         *
         * This function create a string of the Polygon, formated like :
         * (Point1, Point2, ...., Pointn)
         * 
         * \return A string of the Polygon definition
         */
        string toString() const {
            string result = "(";
            auto it = points.begin();
            while(it != points.end()) {
                result += it->toString();
                ++it;
                if (it != points.end()) 
                    result += ", ";
            }
            result += ")";
            return result;
        }

        /**
         * \brief Gets the perimeter of a n-dim polygon.
         *
         * This public method returns the sum of the distances between the adjacents
         * 2 n-dim points defining the polygon.
         * 
         * \return The length (float) of the n-dim polygon
         */
        float perimeter() {
            float total = 0;
            auto it = points.begin();
            for(; it != points.end(); ++it) {
                auto nextIt = next(it);
                if (nextIt != points.end())
                    //Add to distance with next point to total perimeter
                    total += it->distanceFrom(*nextIt);
            }
            //Add distance between first and last point
            total += points.front().distanceFrom(points.back());
            return total;
        }
};

#endif
