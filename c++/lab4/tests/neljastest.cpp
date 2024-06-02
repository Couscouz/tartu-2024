/**
 * \file neljastest.cpp
 * \brief Header file of Tests of the neljastest classes.
 *
 * This file contains a full running of the neljastest classes
 */

#include <cstdlib>
#include <iostream>
#include <cmath>

#include "neljas.h" /**< All our classes */

using namespace std; /* Elements from std namespace */

int test_passed = 0; /**< Number of tests performed */
int test_successful = 0; /**< Number of tests successful */

//All entities comparisons are string made
#define TEST(a,b,b2,c,c2) cout << "Test " << ++test_passed << ". " << a << ": " << (cmpf(b,b2) && cmpf(c,c2) ? (++test_successful, "OK") :"FAIL") << endl
#define TEST2(a,b,b2,c,c2) cout << "Test " << ++test_passed << ". " << a << ": " << (cmpresult(b,c,b2,c2) ? (++test_successful, "OK") :"FAIL") << endl

//Comparing floats
bool cmpf (double a, double b) {
	if (fabs (a - b) < 0.001f) 
		return true;
	return false;
}

//Comparing 4 doubles
bool cmpresult (double s1, double s2, double r1, double r2) {
	return (cmpf (s1, r1) && cmpf (s2, r2)) || (cmpf (s1, r2) && cmpf (s2, r1));
}


int main (int argc, char* argv[]) {

	// Task 1: swapping
	cout << "--Exercise 1: Exchange the value of two variables with a reference and a pointer" << endl;
	double x = 1.0, y = -2.0;
	swap_ref<double> (x, y);
	TEST("swap_ref<double> (x, y)(-2,1)", x, -2.0, y, 1.0);
	swap_ptr<double> (&x, &y);
	TEST("swap_ptr<double> (&x, &y)(1,-2)", x, 1.0, y, -2.0);

	// Task 2: equation
	cout << "--Exercise 2. Function to solve an equation" << endl;
	double a = 1.0, b = -2.0, c = 1.0;
	double solution1 = 0, solution2 = 0;	// solutions could be 1 and 1
	if (solve (a, b, c, solution1, solution2)) {
	cout << "The solutions are: " << solution1 << ", " << solution2 << endl;
    } else {
    	cout << "There are no real number solutions!" << endl;	
    }
	TEST2("solve (1, -2, 1, s1, s2)(1,1)", solution1, 1, solution2, 1);
    // with a==0
    solve(0, -2, 1, solution1, solution2);
    TEST2("solve (0, -2, 1, s1, s2)(0.5,0.5)", solution1, 0.5, solution2, 0.5);

	// Task 3
	Point2 p1 {1.0, 2.0}; Point2 p2 {0,0}; Point2 p3 {5.0, 2.0};
	DynamicLine<Point2> l1 {&p1, &p2};	// the section between p1 and p2
	DynamicLine<Point2> l2 {nullptr, nullptr};
	l2 = l1;		// copy paragraph l1 (the vertices remain the same)
	l2.p2 = &p3;				// we define the second endpoint of l2
	p1.x = 2.0;
    DynamicLine<Point2> l3 {l2};
    TEST2("DynamicLine<> copy constructor 1/2", l3.p1->x, l2.p1->x, l3.p1->y, l2.p1->y);
    TEST2("DynamicLine<> copy constructor 2/2", l3.p2->x, l2.p2->x, l3.p2->y, l2.p2->y);

    DynamicLine<Point2> l4 = l3;
    TEST2("DynamicLine<> assginement operator 1/2", l3.p1->x, l4.p1->x, l3.p1->y, l4.p1->y);
    TEST2("DynamicLine<> assginement operator 2/2", l3.p2->x, l4.p2->x, l3.p2->y, l4.p2->y);

    cout << "(" << *(l4.p1) << "-" << *(l4.p2) << ")" << endl;

	// Task 4
	MyArray<int> numbers;			// sequence of figures
	numbers.addElement (5);			// we add one element
	numbers.addElement (11);		// and one more
	MyArray<int> copy = numbers;	// copy sequence (copy constructor)
	copy.addElement (13);			// we add an element to the copy
	MyArray<int> copy2;
	copy2 = numbers;				// we use the assignment operator

	if (numbers.getSize () != 2 || copy.getSize () != 3 || copy2.getSize () != 2)	// check the sizes 
		cout << "Copy failed – wrong sizes!" << endl;
	if (numbers.elementAt(0) != copy.elementAt(0) || numbers.elementAt(1) != copy.elementAt(1)) // check the content
		cout << "Copy failed – wrong elements!" << endl;
    TEST("Checking sizes", copy.getSize(), 3, copy2.getSize(), 2);
    TEST2("Checking elements", numbers.elementAt(0), copy.elementAt(0), numbers.elementAt(1), copy.elementAt(1));

	cout << "--------ENDING--------" << endl;

    //Conclusion with final count
	cout << "Number of tests passed: " << test_passed << endl;
    cout << "Number of success: " << test_successful << endl;

	return EXIT_SUCCESS;
}
