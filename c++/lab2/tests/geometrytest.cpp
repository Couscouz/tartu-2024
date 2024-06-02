/**
 * \file geometrytest.cpp
 * \brief Header file of Tests of the Geometry library.
 *
 * This file contains a full running of the Geometric library in 2D and 3D
 */

#include "geometry.h" /**< All our classes */
#include <iostream> /**< Input and output */
#include <cmath> /**< sqrt() & pow() needed */

using namespace std; /* Elements from std namespace */

int test_passed = 0; /**< Number of tests performed */
int test_successful = 0; /**< Number of tests successful */

/**
 * \brief Compare 1 pair of values for unit tests.
 *
 * This macro is used to perform 1 test and prints whether it passed or failed.
 */ 
#define TEST1(a,b,b2) cout << "Test " << ++test_passed << ". " << a << ": " << (cmpf(b,b2) ? (++test_successful, "OK") :"FAIL") << endl

/**
 * \brief Compare 2 pairs of values for unit tests.
 *
 * This macro is used to perform 2 test and prints whether it passed or failed.
 */ 
#define TEST2(a,b,b2,c,c2) cout << "Test " << ++test_passed << ". " << a << ": " << ((cmpf(b,b2) && cmpf(c,c2)) ? (++test_successful, "OK") :"FAIL") << endl

/**
 * \brief Compare 3 pairs of values for unit tests.
 *
 * This macro is used to perform 3 test and prints whether it passed or failed.
 */ 
#define TEST3(a,b,b2,c,c2, d, d2) cout << "Test " << ++test_passed << ". " << a << ": " << ((cmpf(b,b2) && cmpf(c,c2) && cmpf(d,d2)) ? (++test_successful, "OK") :"FAIL") << endl

/**
 * \brief Compare 2 floats.
 *
 * This method indicate if the 2 values are equal (with a padding of 0.001f)
 * 
 * \param a The first value (float)
 * \param b The second value (float)
 * \return Boolean telling if the value are equals
 */
bool cmpf (float a, float b) {
	return (fabs (a - b) < 0.001f) ;
}

/**
 * \brief Main testing function.
 *
 * This is the entry point of the test program.
 * Print result of each test
 * 
 * \return 0 on successful execution.
 */
int main (int argc, char* argv[]) {

	//Point2
	cout << "--Test class Point2--" << endl;
	// Require default constructor 
	Point2 v1;
	// Require public coordinates x and y
	cout << v1.x << " " << v1.y << endl;
	// Testi Point2 vaikekonstruktorit
	TEST2("Point2 default constructor v1(0,0)", v1.x, 0, v1.y, 0);
	// Require constructor with two parameters
	Point2 v2 {1.0, -1.0}; // c++11 
	TEST2("Point2 constructor v2(1,-1)", v2.x, 1, v2.y, -1);
	// Require distanceFrom method
    TEST1("Point2 v1(0,0) distance from v2(1,-1)", v1.distanceFrom(v2), sqrt(2));
	//cout << "v1(0,0) distance from v2(1,-1) is " << v1.distanceFrom(v2) << endl;
	// Require operator <<
    cout << "Point2 v2: " << v2 << endl;


    // Line2
    cout << "--Test class Line2--" << endl;
	// Require default constructor
	Line2 l1;
	// Require public points p1 and p2
	cout << "l1 : " << l1.p1 << "-" << l1.p2 << endl;
    //Test Line2 constructor
    Point2 _p;
    TEST2("Line2 default constructor l1(0,0)", l1.p1.x, _p.x, l1.p1.y, _p.y);
	// Require constructor with two parameters
	Line2 l2 {v1, v2};
    TEST2("Line2 constructor l2{v1,v2}", l2.p1.x, v1.x, l2.p1.y, v1.y);
	TEST2("Line2 constructor l2{v1,v2}", l2.p2.x, v2.x, l2.p2.y, v2.y);
	// Require method length
    TEST2("Line2 l2 length sqrt(2)", l2.length(), sqrt(2), 0, 0);
	// Require operator <<
	cout << "Line2 l2: " << l2 << endl;
    
    // Circle2
    cout << "--Test class Circle2--" << endl;
	// Require default constructor
	Circle2 c1;
	// Require variable p1
	cout << c1.p1 << endl;
	// Require variable r
	cout << c1.r << endl;
    //Test default constructor Circle2
    TEST3("Circle2 default constructor", c1.p1.x, _p.x, c1.p1.y, _p.y, c1.r, 1);
	// Require constructor with point and a radius
	Circle2 c2 {v1, 2.0};
    //Test constructor Circle2
    TEST3("Circle2 constructor c2{v1,2.0}", c2.p1.x, _p.x, c2.p1.y, _p.y, c2.r, 2.0);
	// Require method circumference
	float f = c1.circumference();
    TEST1("Circle2 c1 circumference is 2*pi*r", f, 2*M_PI);
	// Require method area
	f = c1.area();
    TEST1("Circle2 c1 area is pi*r*r", f, M_PI);
	// Require method contains(Point2)
	bool b = c1.contains(v1);
    TEST1("Circle2 c1 contains v1(0,0)", b, true);
	// Require method contains(Line2)
	b = c1.contains(l1);
    TEST1("Circle2 c1 contains l1((0,0)-(1,-1))", b, true);
    // Require method scale
    float oldRadius = c1.r;
	c1.scale(2.0);
    TEST1("Circle2 c1 scaled by 2", c1.r, oldRadius*2.0);
	// Require operator <<
	cout << "Circle2 c1: " << c1 << endl;


	// Point3
    cout << "--Test class Point3--" << endl;
	// Require default constructor
	Point3 v3_1;
	// Require public coordinates x, y and z
	cout << v3_1.x << " " << v3_1.y << " " << v3_1.z << endl;
    //Test default constructor Point3
    TEST3("Point3 default constructor", v3_1.x, 0, v3_1.y, 0, v3_1.z, 0);
	// Require constructor with three parameters
	Point3 v3_2 {1.0, 0.0, -1.0};
    //Test constructor Point3
    TEST3("Point3 constructor", v3_2.x, 1.0, v3_2.y, 0, v3_2.z, -1.0);
	// Require method distanceFrom
	f = v3_1.distanceFrom (v3_2);
    TEST1("Point3 v3_1 distance from v3_2", f, sqrt(2));
	// Require operator <<
	cout << "Point3 v3_1:" << v3_1 << endl;

	// Line3
    cout << "--Test class Point3--" << endl;
	// Require default constructor
	Line3 l3_1;
    //Test default constructor Point3
    TEST3("Line3 default constructor", l3_1.p1.x, 0, l3_1.p2.y, 0, l3_1.p1.z, 0);
	// Require constructor with two parameters
	Line3 l3_2 {v3_1, v3_2};
    //Test constructor Point3
    TEST3("Line3 constructor l3_2.p1", l3_2.p1.x, 0, l3_2.p1.y, 0, l3_2.p1.z, 0);
	TEST3("Line3 constructor l3_2.p2", l3_2.p2.x, 1.0, l3_2.p2.y, 0, l3_2.p2.z, -1.0);
    // Require method length
	f = l3_2.length();
    TEST1("Line3 length l3_2", f, sqrt(2));
	// Require operator <<
	cout << "Line3 l3_2: " << l3_2 << endl;

	// Sphere3
    cout << "--Test class Sphere3--" << endl;
	// Require default constructor
	Sphere3 s3_1;
    //Test default constructor Sphere3
    TEST3("Sphere3 default constructor s3_1", s3_1.p1.x, 0, s3_1.p1.z, 0, s3_1.r, 1.0);
	// Require constructor with point and a radius
	Sphere3 s3_2 {v3_2, 2.0};
    //Test constructor Sphere3
    TEST3("Sphere3 constructor s3_2", s3_2.p1.x, 1.0, s3_2.p1.z, -1.0, s3_2.r, 2.0);
	// Require method circumference
	f = s3_1.circumference();
    TEST1("Sphere3 s3_1 circumference is 2*pi*r", f, 2*M_PI);
	// Require method volume
	f = s3_1.volume();
    TEST1("Sphere3 s3_1 volume is pi*r^3", f, M_PI);
	// Require method contains(Point3)
	b = s3_1.contains(v3_1);
    TEST1("Sphere3 s3_1 contains Point3 v3_1", b, true);
	// Require method contains(Line3)
	b = s3_1.contains(l3_1);
    TEST1("Sphere3 s3_1 contains Line3 l3_1", b, true);
	// Require method scale
    oldRadius = s3_1.r;
	s3_1.scale(2.0);
    TEST1("Sphere3 s3_1 scaled by 2", s3_1.r, oldRadius*2.0);
	// Require operator <<
	cout << "Sphere3 s3_1: " << s3_1 << endl;

    cout << "--------ENDING--------" << endl;

    //Conclusion with final count
	cout << "Number of tests passed: " << test_passed << endl;
    cout << "Number of success: " << test_successful << endl;

	return EXIT_SUCCESS;
}
