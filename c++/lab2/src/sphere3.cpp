/**
 * \file sphere3.cpp
 * \brief Methods of the class Sphere3.
 *
 * This file contains all the methods definitions of the class Sphere3.
 */

#include "sphere3.h" /* Header file - Our own features */
#include <cmath> /**< PI constant needed */


Sphere3::Sphere3(Point3 np1, float nr)
: p1 {np1}, r {nr}
{
    if (r < 0) r = 0;
}

float Sphere3::circumference () {
	return 2*M_PI*r;
}

float Sphere3::area () {
	return M_PI*r*r;
}

float Sphere3::volume () {
	return M_PI*r*r*r;
}

bool Sphere3::contains (Point3 p) {
    return (p1.distanceFrom(p) <= r);
}

bool Sphere3::contains (Line3 l) {
    return (p1.distanceFrom(l.p1) <= r && p1.distanceFrom(l.p2) <= r);
}

void Sphere3::scale (float factor) {
    r = r*factor;
    if (r < 0) r = 0;
}

std::ostream& operator<<(ostream& o, const Sphere3& s) {
    o << "(" << s.p1 << "," << s.r << ")";
    return o;
}