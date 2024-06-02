/**
 * \file MyArray.h
 * \brief Header file of MyArray<T>.
 *
 * This file contains all functions for MyArray<T>.
 */

#ifndef MYARRAY_H
#define MYARRAY_H

#include <algorithm> /* std::copy needed */

template <class T>
class MyArray {
    private:
        unsigned int size; /* Number of elements in the array */

    public:
        T* content; /* Array content */

        /**
         * \brief Default constructor.
         *
         * This public method setup empty array (size 0).
         */
        MyArray () {
            size = 0;
            content = new T[0];
        };

        /**
         * \brief Copy constructor.
         *
         * This public method copy reference value.
         * \param a The reference of a MyArray variable (MyArray&)
         */
        MyArray (const MyArray& a) {
            size = a.size;
            content = new T[size];
            std::copy(a.content, a.content+size, content);
        };
        
        /**
         * \brief Assignement operator.
         *
         * This public method get value of MyArray ref and copy it to current one
         * \param a The reference of a MyArray variable (MyArray&)
         */
        MyArray& operator= (const MyArray& a) {
            //if a is not this ar
            if (this != &a) {
                size = a.size;
                content = new T[size];
                std::copy(a.content, a.content+size, content);
            }
            return *this;
        };

        /**
         * \brief Destructor.
         *
         * This public method destroy the object by setting size to 0 and unallocating elements.
         */
        ~MyArray () {
            size = 0;
            delete[] content;
        };

        /**
         * \brief Size getter.
         *
         * This public method return  empty array (size 0).
         * \return size 
         */
        unsigned int getSize () {
            return size;
        };

        /**
         * \brief Accessing element of the array.
         *
         * This public method add an element to the array content
         * \param element The element (T) to add
         */
        void addElement (T element) {
            T* newArray = new T[size+1];
            std::copy(content, content+size, newArray);
            newArray[size] = element;
            size++;
            content = newArray;
        };

        /**
         * \brief Accessing element of the array.
         *
         * This public method is use to get the value an element in the array
         * \param i The index (int) of the object to get, if not in range throw error
         * \return a reference to the element
         */
        T& elementAt (unsigned int i) {
            //if index is range of possibles
            if (i >= size) {
                throw std::out_of_range("Index out of range");
            }
            return content[i];
        };
};

#endif // MYARRAY_H