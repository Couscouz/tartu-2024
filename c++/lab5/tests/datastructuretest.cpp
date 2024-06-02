/**
 * \file datastructuretest.cpp
 * \brief Header file of Tests of the container librairy.
 *
 * This file contains a full running of the classes
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath> /**< rand() needed */

#include "container.h" /**< All our classes */

using namespace std; /* Elements from std namespace */

int main()
{  
	cout << "============================== Stack Test ===========================" << endl;
	cout << "|=====> Push elements to s1 <=====|" << endl;

    Stack s1;
    int added_numbers = 0;
    int temp;

    while (added_numbers != 5) {
        temp = s1.Gen_Random_Number();
        if (s1.isPrim(temp)) {
            //if number is prime, then pushing it to the stack
            s1.push(temp);
            added_numbers++;
        }
    }
    //s1.print();
	cout << "|=====> Sorting s1 elements into s2 <=====|" << endl;

	Stack s2 = s1.Sort_Prim_Numbers(s1);

	cout << "|=====> Pop elements from s2 <=====|" << endl;
	
    //inline printer of the stack
    while (!s2.isEmpty()) {
        cout << s2.pop() << " ";
    }
    cout << endl;
    
	cout << "================================= End ===============================" << endl;

    
	cout << "============================== Queue Test ===========================" << endl;
	Queue<int> q1;
	cout << "|=====> Check Queue is empty <=====|" << endl;
	q1.DeQueue();  
	cout <<  "Done!! " << endl;
	cout << "|=====> Push elements to Queue <=====| " << endl;
	srand(time(0));
	q1.EnQueue(rand()%10);
	q1.EnQueue(rand()%10);
	q1.EnQueue(rand()%10);
	q1.EnQueue(rand()%10);
	q1.EnQueue(rand()%10);
	cout <<endl<< "Done!! " << endl;
	cout << "|=====> Check Queue is full <=====|" << endl;
	q1.EnQueue(60);
	cout << "Done!! " << endl;
	cout << "|=====> Display Queue elements <=====|" << endl;
	q1.PrintQueue();
	cout << "Done!! " << endl;
	cout << "|=====> Delete element <=====|" << endl;
	q1.DeQueue();
	cout << "Done!! " << endl;
	cout << "|=====> Display Queue elements <=====|" << endl;
	q1.PrintQueue();
	cout << "Done!! " << endl;
	cout << "|=====> Search in Queue <=====|" << endl;
	Queue<int> q2;
	for(int i = 0; i < MAX_SIZE; i++)
		q2.EnQueue(rand()%10);
    q2.PrintQueue();
	cout << "Enter a number to search: ";
	int num;
	cin >> num;
	q2.Search(num);
	cout << endl << "================================= End ===============================" << endl;
    
	cout << "=========================== Linked list Test ========================" << endl;
	Linkedlist list;
	list.addNode(10);
	list.addNode(20);
	list.addNode(30);
	list.addNode(40);
	list.addNode(50);
	list.addNode(60);
	list.addNode(70);
	list.addNode(80);
	list.addNode(90);
	cout << "Elements of the list are: ";
	list.printList();
	cout << "Length list is : " << list.lengthList() << endl;
	
    list.deleteNode_Index(2);
	cout << "Elements of the list are: ";
	list.printList();
	cout << "Length list is : " << list.lengthList() << endl;
	list.deleteNode_Index(2);
	cout << "Elements of the list are: ";
	list.printList();
	cout << "Length list is : " << list.lengthList() << endl;
	list.deleteNode_Data(40);
	cout << "Elements of the list are: ";
	list.printList();
	cout << "-----------------------------------------" << endl;
	list.isRange(200);
	list.searchNode(200);
	list.searchNode(10);
	cout << endl << "================================= End ===============================" << endl;
    
	system("pause");
	return 0;
}