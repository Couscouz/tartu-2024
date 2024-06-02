/**
 * \file Point2.cpp
 * \brief Methods of the class Point2.
 *
 * This file contains all the methods definitions of the class Point2.
 */

#include "Point2.h" /**< Our class definition */
#include <cmath> /**< sqrt() needed */

using namespace std; /**< Elements from std namespace */


Point2::Point2(float nx, float ny)
	: x {nx}
  	, y {ny}
{
}


float Point2::distanceFrom(Point2 v) {
    return sqrt( (x - v.x)*(x - v.x) + (y - v.y)*(y - v.y) ); 
}

ostream& operator << (ostream& os, Point2 v) {
	return os << "(" << v.x << "," << v.y << ")";
}
