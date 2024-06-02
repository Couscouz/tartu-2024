/**
 * \file Linkedlist.cpp
 * \brief Methods of the class Linkedlist.
 *
 * This file contains all the methods definitions of the class Linkedlist.
 */

#include "Linkedlist.h" /**< Our class definition */
#include <iostream> /**< cout and endl needed */

using namespace std;


Linkedlist::Linkedlist() {
    head = NULL;
};

void Linkedlist::addNode(int x) {
    Node* newNode = new Node(x);
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
};

void Linkedlist::printList() {
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
};

void Linkedlist::deleteNode_Index(int i) {
    i--;
    if (head == NULL) {
        return;
    }

    Node* temp = head;
    if (i == 0) {
        head = head->next;
        delete temp;
    } else {
        int count = 0;
        
        while (temp != NULL && count < i - 1) {
            temp = temp->next;
            count++;
        }

        if (temp == NULL || temp->next == NULL) {
            cout << "Index out of range" << endl;
            return;
        } else {
            Node* nodeToDelete = temp->next;
            temp->next = temp->next->next;
            delete nodeToDelete;
        }
    }
};

bool Linkedlist::isListEmpty() {
    return (head == NULL);
};

int Linkedlist::lengthList() {
    int length = 0;
    Node* temp = head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
};

bool Linkedlist::isRange(int i) {
    if (i >= lengthList())
        cout << "Index out of range" << endl;
    return !(i >= lengthList());
};

void Linkedlist::deleteNode_Data(int x) {
    Node* temp = head;
    Node* prev = NULL;

    if (temp != NULL && temp->data == x) {
        head = temp->next;
        delete temp;
    } else {
        while (temp != NULL && temp->data != x) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << x << "is not present at the Linked list" << endl;
        } else {
            prev->next = temp->next;
            delete temp;
        }
    }
};

void Linkedlist::searchNode(int x) {
    Node* temp = head;
    int pos = 0;

    while (temp != NULL && temp->data != x) {
        temp = temp->next;
        pos++;
    }

    if (temp == NULL) {
        cout << x << " is not present at the Linked list" << endl;
    } else {
        cout << x << " is present at the Linked List in location: " << &pos << endl;
    }
};