/**
 * \file Stack.h
 * \brief Methods of the class Stack.
 *
 * This file contains all the methods definitions of the class Stack.
 */

#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 5 //cause why not

/**
 * \brief Class representing a Stack
 *
 * Classical Stack representation, with additionnal methods for Prime numbers
 */
class Stack {
    private:
        //index of head
        int head;

    public:
        //the stack
        int* stack_array = new int[MAX_SIZE];
        
        Stack(); /**< Default constructor */
        
        /**
         * \brief Push item into the stack
         *
         * This public method push an integer into the stack.
         * 
         * \param x The integer to push x (int)
         * \return true if integer was added, false ifnot
         */
        bool push(int x);

        /**
         * \brief Pop top element from the stack and return it
         *
         * This public method remove and return top element of the stack
         * 
         * \return the element, -1 if the stack is empty
         */
        int pop();

        /**
         * \brief Read an element from the stack and return it
         *
         * This public method read an element from the stack and return it
         * 
         * \return the element, -1 if the stack is empty
         */
        int peek();

        /**
         * \brief Check that the stack is empty
         *
         * This public method check that the stack is empty
         * 
         * \return true is the stack is empty, false if not
         */
        bool isEmpty();

        /**
         * \brief Check that the stack is full
         *
         * This public method check that the stack is full
         * 
         * \return true is the stack is full, false if not
         */
        bool isFull();

        /**
         * \brief Check if an interger is Prime
         *
         * This public method check if the given integer is a Prime number (only dividable by 1 and himself)
         * 
         * \param x The integer to check x (int)
         * \return true is the number is prime, false if not
         */
        bool isPrim(int x);
        
        /**
         * \brief Generate a random number between 0 and 999
         *
         * This public method generate a random number between 0 and 999
         *
         * \return the generated integer
         */
        int Gen_Random_Number();

        /**
         * \brief Check if an interger is Prime
         *
         * This public method sort a Stack by decreasing order, and return the resulting one
         * 
         * \param input The stack to sort input (Stack&)
         * \return the resulted sorted stack
         */
        Stack Sort_Prim_Numbers(Stack &input);
};
#endif
