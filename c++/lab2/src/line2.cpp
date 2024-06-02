/**
 * \file line2.cpp
 * \brief Methods of the class Line2.
 *
 * This file contains all the methods definitions of the class Line2.
 */

#include "line2.h" /* Header file - Our own features */


Line2::Line2(Point2 np1, Point2 np2)
: p1 {np1}, p2 {np2}
{
}

float Line2::length () {
	return p1.distanceFrom(p2);
}

ostream& operator<<(ostream& o, const Line2& l) {
    o << "(" << l.p1 << " - " << l.p2 << ")";
    return o;
}