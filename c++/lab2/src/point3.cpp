/**
 * \file point3.cpp
 * \brief Methods of the class Point3.
 *
 * This file contains all the methods definitions of the class Point3.
 */

#include "point3.h" /* Header file - Our own features */
#include <cmath> /**< sqrt() & pow() needed */


Point3::Point3(float nx, float ny, float nz)
: x {nx}, 
  y {ny},
  z {nz}
{
}

float Point3::distanceFrom (Point3 p) {
    float dif_x = p.x - x;
    float dif_y = p.y - y;
    float dif_z = p.z - z;
	return sqrt(pow(dif_x, 2) + pow(dif_y, 2) + pow(dif_z, 2));
}

ostream& operator<<(ostream& o, const Point3& p) {
    o << "(" << p.x << "," << p.y << "," << p.z << ")";
    return o;
}