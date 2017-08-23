#pragma once

/////////////////////////////////////////////////////////////////////////
//Trie.h-it contains all the functionality for creating trie data structure//
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
creating the trie data structure
supporting all the operations like
searching in the trie data structure
add a word in the trie data structure
retriving the vector of words that contain the given prefix word

Public Interface:
=================
Trie* trie = new Trie();
trie->addword(std::string)               //adding  a word to trie data structure
trie->searchword(std::string)            //searching a word in trie data structure
trie->retrive(std::string)               //retriving the word that contain the given prefix


Build Process:
==============
Required files
Trie.h,Trie.cpp

Build commands (either one)
- devenv Trie.sln

Maintenance History:
====================
ver 1.0 : 13th march 2017
-first release

*/

#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
	Node() { mContent = ' '; mMarker = false; }
	~Node() {}
	char content() { return mContent; }
	void setContent(char c) { mContent = c; }
	bool wordMarker() { return mMarker; }
	void setWordMarker() { mMarker = true; }
	Node* findChild(char c);
	void appendChild(Node* child) { mChildren.push_back(child); }
	vector<Node*> children() { return mChildren; }
	string retrieve(string input, int charLocation);
private:
	char mContent;
	bool mMarker;
	vector<Node*> mChildren;
};

class Trie {
public:
	Trie();
	~Trie();
	void addWord(string s);
	bool searchWord(string s);
	string retrieve(string word);
private:
	Node* root;
};

Node* Node::findChild(char c)
{
	for (int i = 0; i < mChildren.size(); i++)
	{
		Node* tmp = mChildren.at(i);
		if (tmp->content() == c)
		{
			return tmp;
		}
	}

	return NULL;
}

Trie::Trie()
{
	root = new Node();
}

Trie::~Trie()
{
	// Free memory
}

//logic for adding the word in to the trie data structure

void Trie::addWord(string s)
{
	Node* current = root;

	if (s.length() == 0)
	{
		current->setWordMarker(); // an empty word
		return;
	}

	for (int i = 0; i < s.length(); i++)
	{
		Node* child = current->findChild(s[i]);
		if (child != NULL)
		{
			current = child;
		}
		else
		{
			Node* tmp = new Node();
			tmp->setContent(s[i]);
			current->appendChild(tmp);
			current = tmp;
		}
		if (i == s.length() - 1)
		{
			current->setWordMarker();
			Node* EndNode = new Node();
			EndNode->setContent('\0');
			current->appendChild(EndNode);
		}
	}
}


//logic for searching the word in the trie data structure

bool Trie::searchWord(string s)
{
	Node* current = root;

	while (current != NULL)
	{
		for (int i = 0; i < s.length(); i++)
		{
			Node* tmp = current->findChild(s[i]);
			if (tmp == NULL)
				return false;
			current = tmp;
		}

		if (current->wordMarker())
			return true;
		else
			return false;
	}

	return false;
}

//logic for retriving the word that conatin the given prefix word

string Node::retrieve(string input, int charLocation)
{
	string output = "";

	if (charLocation <= input.length() - 1)
	{
		//Get to correct branch
		vector<Node*>::iterator child;


		for (child = mChildren.begin(); child != mChildren.end(); child++)
		{
			if ((*child)->mContent == input[charLocation])
				break;
		}
		if (child == mChildren.end())
			return "";
		else
		{
			return (*child)->retrieve(input, charLocation + 1);
		}
	}
	else if (mContent == '\0')
	{
		return input + "\n";
	}
	else if (charLocation == input.length())
	{
		for (vector<Node*>::iterator child = mChildren.begin(); child != mChildren.end(); child++)
		{
			output += (*child)->retrieve(input, charLocation + 1);
		}
		return output;
	}
	else
	{
		//All the subsequent strings will be recommendations
		for (vector<Node*>::iterator child = mChildren.begin(); child != mChildren.end(); child++)
		{
			output += (*child)->retrieve(input + mContent, charLocation + 1);
		}

		return output;
	}


}

//calling the retrive function with the given word and character position 0
string Trie::retrieve(string word)
{
	Node* current = root;
	string ouput;
	ouput = current->retrieve(word, 0);
	return ouput;
}

