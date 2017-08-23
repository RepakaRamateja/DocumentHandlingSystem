#pragma once
/////////////////////////////////////////////////////////////////////////
//Queue.h-it contains all the functionality for creating queuw data structure//
//                                                                     //
// Language:    Visual C++ 2012                                        //
// Platform:    Lenova ThinkPad E420s, Windows 7                       //
// Application: Spell Checker - ADS, Pr#3, Spring 2017                 //
// Author:       repaka ramateja,            Syracuse University       //
//              (315) 395-9575, rrepaka@syr.edu                        //
// Source:  wikipedia                                                  //
/////////////////////////////////////////////////////////////////////////

/*
Package Operations:
==================
this package defines all the operations that are used for:
creating the queue
inserting the word into a queue
deletion of word from a queue

Public Interface:
=================
Queue que;
que.enque("word")     //inserts the word into a queue
que.deque();          // retrieves the word from a queue


Build Process:
==============
Required files
Queue.h,Queue.cpp

Build commands (either one)
- devenv Queue.sln

Maintenance History:
====================
ver 1.0 : 13th march 2017
-first release

*/
#include<iostream>
#include<cstdlib>
#include<string>

struct node {
	std::string info;
	struct node *next;
};
class Queue {

private:

	node *rear;

	node *front;


public:

	Queue();

	void enqueue(std::string);

	std::string dequeue();

	long size();

	void display();

};

Queue::Queue() {

	rear = NULL;

	front = NULL;

}

//inserts the word into a queue

void Queue::enqueue(std::string value)
{

	node *temp = new node;

	temp->info = value;

	temp->next = NULL;

	if (front == NULL) {

		front = temp;

	}
	else {

		rear->next = temp;

	}

	rear = temp;

}

//returns the word from a queue
std::string Queue::dequeue() {

	node *temp = new node;

	std::string value;

	if (front == NULL) {

		std::cout << "\nQueue is Emtpty\n";

	}
	else {

		temp = front;

		front = front->next;

		value = temp->info;

		delete temp;
	}
	return value;
}

//returns all the elements in the queue
void Queue::display() {

	node *p = new node;

	p = front;

	if (front == NULL) {

		std::cout << "\nNothing to Display\n";

	}
	else {

		while (p != NULL) {

			std::cout << std::endl << p->info;

			p = p->next;

		}

	}

}

//returns the size of the queue
long Queue::size()
{
	node *p = new node;
	long count = 0;


	p = front;

	if (front == NULL)
	{
		std::cout << "\nNothing to Display\n";
	}
	else
	{

		while (p != NULL) {
			count++;
			p = p->next;

		}

	}

	return count;

}