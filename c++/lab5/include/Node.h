/**
 * \file Node.h
 * \brief Methods of the class Node.
 *
 * This file contains all the methods definitions of the class Node.
 */

#ifndef NODE_H
#define NODE_H

#include<iostream>

class Node {
public:
	int data;
	Node* next;
    
    Node() {
        data = 0;
        next = NULL;
    };

    // Parameterised Constructor
    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    };
};
#endif
