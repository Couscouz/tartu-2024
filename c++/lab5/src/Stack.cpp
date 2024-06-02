/**
 * \file Stack.cpp
 * \brief Methods of the class Stack.
 *
 * This file contains all the methods definitions of the class Stack.
 */

#include "Stack.h" /**< Our class definition */
#include <cmath> /**< rand() needed */
#include <iostream> /**< cout and endl needed */

using namespace std; /* Elements from std namespace */

Stack::Stack() {
    head = -1;
}

bool Stack::push(int x) {
    //we check if the size is okay
    if (!isFull()) {
        cout << x << " pushed" << endl;
        stack_array[++head] = x; //increment head and push the element
        return true;
    } else {
        return false;
    }
}

int Stack::pop() {
    if (isEmpty()) {
        //stack is 
        return -1; //error
    }
    return stack_array[head--]; // Return top element and decrement head
}

int Stack::peek() {
    if (isEmpty()) {
        //stack is 
        return -1; //error
    }
    return stack_array[head]; // Return the top element without removing it
}

bool Stack::isEmpty() {
    return (head < 0); //is -1
}

bool Stack::isFull() {
    return (head >= MAX_SIZE);
}

bool Stack::isPrim(int x) {
    if (x <= 1)
        return false;
    for (int i = 2; i <= x / 2; i++)
        if (x % i == 0)
            return false;
    return true;
}

int Stack::Gen_Random_Number() {
    return rand()%1000;
}

Stack Stack::Sort_Prim_Numbers(Stack &input) {
    Stack tmpStack; //temporary stack

    //Stack Sorting
    while (!input.isEmpty()) {
        int tmp = input.peek();

        input.pop();
        // Pop elements from the temporary stack which are greater than the current element
        while (!tmpStack.isEmpty() && tmpStack.peek() > tmp) {
            input.push(tmpStack.pop());
        }

        // Push the current element to the temporary stack
        tmpStack.push(tmp);
    }
    return tmpStack;
}
