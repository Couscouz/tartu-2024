/**
 * \file point2.cpp
 * \brief Methods of the class Point2.
 *
 * This file contains all the methods definitions of the class Point2.
 */

#include "point2.h" /* Header file - Our own features */
#include <cmath> /**< sqrt() & pow() needed */


Point2::Point2(float nx, float ny)
: x {nx}, 
  y {ny}
{
}

float Point2::distanceFrom (Point2 p) {
    float dif_x = p.x - x;
    float dif_y = p.y - y;
	return sqrt(pow(dif_x, 2) + pow(dif_y, 2));
}

ostream& operator<<(ostream& o, const Point2& p) {
    o << "(" << p.x << "," << p.y << ")";
    return o;
}
