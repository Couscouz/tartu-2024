/**
 * \file geometrytest.cpp
 * \brief Header file of Tests of the Geometry classes.
 *
 * This file contains a full running of the Geometric classes
 */

#include <iostream> /**< Input and output */
#include <cmath> /** Needed to basic calculation */
#include <list> /** List needed */
#include <algorithm> /** Needed for remove_if() */
#include <vector> /** Vector needed */

#include "geometry.h" /**< All our classes */
#include "myfunctors.h" /* Bonus task 3.2*/


using namespace std; /* Elements from std namespace */

int test_passed = 0; /**< Number of tests performed */
int test_successful = 0; /**< Number of tests successful */

//All entities comparisons are string made
#define TEST(a,b1,b2) cout << "Test " << ++test_passed << ". " << a << ": " << (cmpf(b1,b2) ? (++test_successful, "OK") :"FAIL") << endl
#define TEST2(a,b1,b2) cout << "Test " << ++test_passed << ". " << a << ": " << (compStr(b1,b2) ? (++test_successful, "OK") :"FAIL") << endl

//Comparing floats
bool cmpf (float a, float b) {
	if (fabs (a - b) < 0.001f) 
		return true;
	return false;
}

//Comparing strings
bool compStr(string actual, string mustBe) { // just to ignore the spaces	
	actual.erase(remove_if(actual.begin(), actual.end(), ::isspace), actual.end());
	mustBe.erase(remove_if(mustBe.begin(), mustBe.end(), ::isspace), mustBe.end());
	return actual == mustBe || "(" + actual + ")" == mustBe;
}


int main (int argc, char* argv[]) {

	// Task 1

	// Point<n>
	cout << "--Test class Point<n>" << endl;
	// Require default constructor 
	Point<2> v1;
    TEST2("Point<n> default constructor", v1.toString(), "(0,0)");
	// Require member coords
	cout << v1.coords.size() << endl;
	TEST("Point<2> default constructor v1.coords.size()(2)", v1.coords.size(), 2);
	// Require constructor with parameters
	Point<2> v2 {list<float> {3.0, 4.0}};
	// Require distanceFrom method
	float f = v1.distanceFrom(v2);
	TEST("Point<2> v1.distanceFrom(v2)(0)", f, 5.0f);
	// Require toString method
	TEST2("Point<2> spec constructor v1(0,0)", v1.toString (), "(0, 0)");
	// Require << operators
	cout << "v2 : " << v2 << endl;


	// Line<V>
    cout << "--Test class Line<V>--" << endl;
	// Require default constructor
	Line< Point<2> > l1;
    //Test default constructor
    Line<Point<2>> temp2 {v1, v1};
    TEST2("Line<T> l1 default constructor", l1.toString(), "((0,0)-(0,0))");
    // Require constructor with two parameters
    Line< Point<2> > l2 {v1, v2};
    //Test Line<T> constructor
    TEST2("Line<T> l1 default constructor", l2.toString(), "((0,0)-(3,4))");
	// Require members p1 and p2
	cout << l1.p1.toString() << "-" << l1.p2.toString () << endl;
	// Require method length
	f = l1.length();
    TEST("Line<T> l2 length 5", l2.length(), 5);
	// Require toString method
	cout << l2.toString() << endl;
    //Test toString method
    TEST2("Line<T> l2 toString", l2.toString(), "((0, 0)-(3, 4))");
	// Require << operators
	cout << "l2 : " << l2 << endl;

	// Sphere<V>
    cout << "--Test class Sphere<V>--" << endl;
	// Require default constructor
	Sphere<Point<2> > c1;
	// Require variable o
	cout << c1.o.toString();
	// Require variable r
	cout << c1.r << endl;
    //Test default constructor Sphere<V>
    TEST2("Sphere<V> default constructor", c1.toString(), "((0,0),0)");
	// Require constructor with vector and a radius
	Sphere< Point<2> > c2 {v1, 1.0};
    //Test constructor Sphere<V>
    TEST2("Sphere<V> constructor c2{v1, ..}", c2.o.toString(), v1.toString());
    TEST("Sphere<V> constructor c2{.., 1.0}", c2.r, 1.0);
	// Require method contains(Point<n>)
	bool b = c1.contains(v1);
    TEST("Sphere<V> c1 contains v1", b, true);
	// Require method contains(Line<Point<n>>)
	b = c2.contains(l1);
    TEST("Sphere<V> c1 contains l1", b, true);
	// Require method scale
	c2.scale(2.0);
    TEST2("Sphere<V> c2 scaled by 2", c2.toString(), "((0,0),2)");
	// Require toString method
	cout << c2.toString () << endl;
    //Test toString method
    TEST2("Sphere<V> c1 toString", c1.toString(), "((0, 0), 0)");
	// Require << operators
	cout << "c2 : " << c2 << endl;

	// Task 2
    cout << "--Test class Polygon<T,n>--" << endl;
	// Require default constructor
	Polygon<Point<2>, 3> triangle;
    //Testing default constructor
    TEST2("Polygon<T,n> default constructor", triangle.toString(), "((0, 0), (0, 0), (0, 0))");
	// Require constructor with parameters
	Polygon<Point<2>, 3> triangle2 {vector< Point<2> >{v1, v2, Point<2> {list<float> {10.0, 10.0}}} };
    //Testing constructor
    TEST2("Polygon<T,n> constructor", triangle2.toString(), "((0, 0), (3, 4), (10, 10))");
	// Require method perimeter
	float y = triangle2.perimeter();
    //Testing method perimeter
    TEST("Polygon<T,n> triangle2 perimeter", y, 5 + sqrt(200) + sqrt(pow(10-3,2)+pow(10-4,2)));
	// Require toString method
	cout << triangle2.toString () << endl;
    //Testing toString method
    TEST2("Polygon<T,n> triangle2 toString", triangle2.toString(), "((0, 0), (3, 4), (10, 10))");
	// Require << operators
	cout << "triangle : " << triangle << endl;


	// Require object SumElements
	SumElements<float> sum;
	// Require operator ()
	sum (1.0);
    sum (5.0);
    sum (6.6);
	// Require method result
	float z = sum.result();
    //Testing if result is good
    TEST("SumElement sum", z, 12.6);

	cout << "--------ENDING--------" << endl;

    //Conclusion with final count
	cout << "Number of tests passed: " << test_passed << endl;
    cout << "Number of success: " << test_successful << endl;

	return EXIT_SUCCESS;
}
