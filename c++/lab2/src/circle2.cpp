/**
 * \file circle2.cpp
 * \brief Methods of the class Circle2.
 *
 * This file contains all the methods definitions of the class Circle2.
 */

#include "circle2.h" /* Header file - Our own features */
#include <cmath> /**< PI constant needed */


Circle2::Circle2(Point2 np1, float nr)
: p1 {np1}, r {nr}
{
    if (r < 0) r = 0;
}

float Circle2::circumference () {
	return 2*M_PI*r;
}

float Circle2::area () {
	return M_PI*r*r;
}

bool Circle2::contains (Point2 p) {
    return (p1.distanceFrom(p) <= r);
}

bool Circle2::contains (Line2 l) {
    return (p1.distanceFrom(l.p1) <= r && p1.distanceFrom(l.p2) <= r);
}

void Circle2::scale (float factor) {
    r = r*factor;
    if (r < 0) r = 0;
}

ostream& operator<<(ostream& o, const Circle2& c) {
    o << "(" << c.p1 << "," << c.r << ")";
    return o;
}