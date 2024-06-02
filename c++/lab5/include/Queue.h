/**
 * \file Queue.h
 * \brief Methods of the class Queue.
 *
 * This file contains all the methods definitions of the class Queue.
 */

#ifndef QUEUE_H
#define QUEUE_H

#define MAX_SIZE 5 //cause why not

#include <iostream>

using namespace std;

/**
 * \brief Class representing a Queue
 *
 * Classical Queue representation
 */
template <class T>
class Queue {
    private:
        T queue_array[MAX_SIZE];
        int front;
        int rear;

    public:
        int data;
        
        //	Initializes the front = -1, rear = -1
        /**< Default constructor */
        Queue() {
            front = -1;
            rear = -1;
        };

        /**
         * \brief Check that the queue is full
         *
         * This public method check that the queue is full
         * 
         * \return true is the queue is full, false if not
         */
        bool isFull() {
            return (rear == MAX_SIZE-1);
        };

        /**
         * \brief Check that the queue is empty
         *
         * This public method check that the queue is empty
         * 
         * \return true is the queue is empty, false if not
         */
        bool isEmpty() {
            return (front == -1 || front > rear);
        };

        /**
         * \brief Add item into the queue
         *
         * This public method queue an item into the queue.
         * 
         * \param x The item to queue x (T)
         */
        void EnQueue(T x) {
            if (isFull()) {
                cout << "Queue is full" << endl;
            } else {
                cout << x << " ";
                queue_array[++rear] = x;
                //if queue was empty previously, marking beginning of the queue
                if (front == -1)
                    front = 0;
            }
        };

        //To remove an element from the queue
        T DeQueue() {
            T element;
            if (isEmpty()) {
                cout << "Queue is empty!!" << endl;
                return -1;
            } else {
                element = queue_array[front];
                cout << "Deleted => " << element << endl;
                if (front >= rear) {
                    front = -1;
                    rear = -1;
                } else {
                    front++;
                }
                return element;
            }
        };

        //	To print out the elements of the queue
        void PrintQueue() {
            cout << "Queue elements : ";
            for (int i = front; i <= rear; ++i) {
                cout << queue_array[i] << "      ";
            }
            cout << endl;
        };

        //To find (x) in queue
        void Search(T x) {
            bool found = false;
            for (int i = front; i <= rear; ++i) {
                if (x == queue_array[i]) {
                    found = true;
                    cout << x << " is present at the Queue in location: " << i << endl;
                }
            }
            if (!found)
                cout << x << " is not present in the Queue" << endl;
        }
};
template class Queue<int>;

#endif
