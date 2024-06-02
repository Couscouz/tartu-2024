/**
 * \file line3.cpp
 * \brief Methods of the class Line3.
 *
 * This file contains all the methods definitions of the class Line3.
 */

#include "line3.h" /* Header file - Our own features */


Line3::Line3(Point3 np1, Point3 np2)
: p1 {np1}, p2 {np2}
{
}

float Line3::length () {
	return p1.distanceFrom(p2);
}

ostream& operator<<(ostream& o, const Line3& l) {
    o << "(" << l.p1 << " - " << l.p2 << ")";
    return o;
}