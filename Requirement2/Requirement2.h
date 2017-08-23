#pragma once

/////////////////////////////////////////////////////////////////////////
//Requirement2.h-it contains all the functionality related to auto completion//
//                                                                     //
// Language:    Visual C++ 2012                                        //
// Platform:    Lenova ThinkPad E420s, Windows 7                       //
// Application: Auto Completion - ADS, Pr#3, Spring 2017             //
// Author:       repaka ramateja,            Syracuse University       //
//              (315) 395-9575, rrepaka@syr.edu                        //
// Source:  wikipedia  and stackoverflow                               //
/////////////////////////////////////////////////////////////////////////

/*
Package Operations:
==================
this package defines all the operations that are used for:
creating the data structure using trie
and adding all the dictionary words
and taking prefix word as input and displaying all the words that start with the given prefix

Public Interface:
=================
Secondrequirement reuire;
reuire.secondrequirement();   //demonstartes second requirement


Build Process:
==============
Required files
Requirement2.h,AutoCompletion.cpp,Trie.h

Build commands (either one)
- devenv Requirement2.sln

Maintenance History:
====================
ver 1.0 : 13th march 2017
-first release

*/

#include"../Trie/Trie.h"
#include<string>
#include<iostream>
#include<vector>
#include<fstream>



class Secondrequirement
{
public:	
	/*logic for creating a trie data structure using dictionary
	taking the input prefix word
	displaying all the words that contain the given prefix
	*/
	void secondrequirement()
	{

		Trie* trie = new Trie();
		std::ifstream infile("../dictionary.txt");

		if (infile)
			std::cout << "able to read the file";
		else
			std::cout << "\nnot able to read the file\n";

		std::string line;
		while (std::getline(infile, line))
		{
			trie->addWord(line);
		}

		std::cout << "\nwords are inserted into the trie data structure\n";
		std::cout << "\nPlease enter the prefix for which you want to test auto completion feature\n";

		std::string prefix;

		std::getline(std::cin, prefix);

		std::string output = trie->retrieve(prefix);

		std::cout << output;
	}


};