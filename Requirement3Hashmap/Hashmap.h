#pragma once
/////////////////////////////////////////////////////////////////////////
// Hashmap.h - it contains all the operations related to the hashmap   //
//                                                                     //
// Language:    Visual C++ 2012                                        //
// Platform:    Lenova ThinkPad E420s, Windows 7                       //
// Application: Document Retrival - ADS, Pr#3, Spring 2017//
// Author:       repaka ramateja,            Syracuse University       //
//              (315) 395-9575, rrepaka@syr.edu                        //
// Source:  wikipedia and github                                       //
/////////////////////////////////////////////////////////////////////////

/*
Package Operations:
==================
this package defines all the operations that are used for:
reading all the given text files and
creating the hashtable(key as word and value as set of files containing that word)






Public Interface:
=================
MapADT map;

insert ---->inserting to hashmap

find------->find an element in hashmap

remove------> remove an element from hashmap

findindex ----> get the index value from the hashmap

Build Process:
==============
Required files
Hashmap.h,Hashmap.cpp

Build commands (either one)
- devenv hashmap.sln

Maintenance History:
====================
ver 1.0 : 13th march 2017
-first release

*/


#pragma once
#include <iostream>
#include <string>
#include <queue>
using namespace std;

class HashMapADT {
public:
	HashMapADT();
	string find(const string& key);
	void insert(const string& key, const string& value);
	void print();
protected:
	unsigned int hash(const string& key);
	int find_index(const string& key, bool override_duplicated_key);
	//const static unsigned int size_max = 20000;
	const static unsigned long size_max = 20000;
	string keys[size_max];
	string values[size_max];
};

HashMapADT::HashMapADT() {
	for (int i = 0; i < size_max; i++) {
		keys[i] = string();
		values[i] = string();
	}
}

//method for generating hash code
unsigned int HashMapADT::hash(const string& k)
{
	//unsigned int value = 0;
	long value = 0;
	for (long i = 0; i < k.length(); i++)
		value = 37 * value + k[i];
	return value;
}

//method to print all the values that are present in the hashmap 
void HashMapADT::print() 
{
	
	for (long i = 0; i < size_max; i++)
		if (!keys[i].empty())
		{
			cout << keys[i] << ":" << "\t" << values[i];
			cout << endl;
		}
}

//method to find an index in an hashmap

int HashMapADT::find_index(const string& key, bool override_duplicate_key = true) {
	//unsigned int h = hash(key) % size_max, offset = 0, index;
	long  h = hash(key) % size_max, offset = 0, index;

	while (offset < size_max) {
		index = (h + offset) % size_max;

		
		if (keys[index].empty() ||
			(override_duplicate_key && keys[index] == key))
			return index;

		offset++;
	}
	return -1;
}

//method to insert an element an element into the hashmap

void HashMapADT::insert(const string& key, const string& value) {
	long index = find_index(key);
	if (index == -1) {
		cerr << "Table is full!" << endl;
		return;
	}

	keys[index] = key;
	values[index] = value;
}

//method to find an element from the hashmap

string HashMapADT::find(const string& key) {
	long index = find_index(key);
	if (index != -1)
		return values[index];

	return "";
}


