/**
 * \file Linkedlist.h
 * \brief Methods of the class Linkedlist.
 *
 * This file contains all the methods definitions of the class Linkedlist.
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h" //Node implementation needed

using namespace std;

/**
 * \brief Class representing a Linkedlist
 *
 * Classical Linkedlist representation, composed of Node each one pointing to the following one
 */
class Linkedlist {
    private:
        //1st node address
        Node* head;
    public:
        //Initializes head = NULL
        Linkedlist(); /**< Default constructor */

        /**
         * \brief Add a node to the linked list
         *
         * This public method add a node to the linked list
         * 
         * \param x The value of the node to add x (int)
         */
        void addNode(int x);

        /**
         * \brief Print the all linked list in 1 line
         *
         * This public method print the all list in 1 line
         */
        void printList();

        /**
         * \brief Delete a node by a given location
         *
         * This public method delete a node by a given location index
         * 
         * \param i The value of the location to delete i (int)
         */
        void deleteNode_Index(int i);

        /**
         * \brief Check that the list is empty
         *
         * This public method check that the list is empty
         * 
         * \return true is the list is empty, false if not
         */
        bool isListEmpty();

        /**
         * \brief Give the list length
         *
         * This public method give the length of the linked list (how many nodes are in the list)
         * 
         * \return the length of the linked list
         */
        int lengthList();

        /**
         * \brief Check if the given location is in list length range
         *
         * This public method check if the given position is in the list length range
         * 
         * \param i The given location i (int)
         * \return true is position is in range, false if not
         */
        bool isRange(int i);

        //Delete a node by a given location content (x)
        /**
         * \brief Delete a node by his content
         *
         * This public method delete the 1st node of the list if the value is similar to the one given
         * 
         * \param x The value of the element to delete (int)
         */
        void deleteNode_Data(int x);

        /**
         * \brief Serch if a value is in the list
         *
         * This public method print statement depending if the value is in the list or not
         * 
         * \param x The value of the element to search for (int)
         */
        void searchNode(int x);
};
#endif
