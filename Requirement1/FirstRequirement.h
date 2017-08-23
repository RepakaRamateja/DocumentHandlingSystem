#pragma once
/////////////////////////////////////////////////////////////////////////
//FirstRequirement.h-it contains all the functionality related to spell checker//
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
creating the data structure using trie 
and searching the trie data structure and detecting the misspelled words
and suggesting some suggestions by forming 1 away distinct words
using insertion deletion and subsituition


Public Interface:
=================
firstrequirement require;
require.requirementone();         //demonstrates first requirement
bsplit()                          //reads a file and split by delimiter;
std::vector<std::string> edits()  //gives one way distinct words


Build Process:
==============
Required files
FirstRequirement.h,Trie.cpp,Trie.h

Build commands (either one)
- devenv Requirement1.sln

Maintenance History:
====================
ver 1.0 : 13th march 2017
-first release

*/

#include "../Trie/Trie.h"
#include<vector>
#include<string>
#include <fstream>
#include<algorithm>
#include"../Queue/Queue.h"
#include<cstdlib>

class firstrequirement
{
public:
	//functions which splits the given line using the delimiter space
	void bsplit(const std::string &s, std::string sep, std::vector<std::string> &read)
	{

		char* cstr = const_cast<char*>(s.c_str());
		char* current;

		current = strtok(cstr, sep.c_str());
		while (current != NULL) {
			read.push_back(current);
			current = strtok(NULL, sep.c_str());
		}


	}

	//function which gives words that are 1 distant away by subsitution insertion and deletion 
	vector<string> edits(string word) {
		vector<string> result;
		string temp;
		for (int i = 0; i < word.length(); i++) {
			temp = word.substr(0, i) + word.substr(i + 1);
			result.push_back(temp);
		}
		for (int i = 0; i < word.length() - 1; i++) {
			temp = word.substr(0, i) + word[i + 1] + word[i] + word.substr(i + 2);
			result.push_back(temp);
		}
		for (int i = 0; i < word.length(); i++) {
			for (char c = 'a'; c <= 'z'; c++) {
				temp = word.substr(0, i) + c + word.substr(i + 1);
				result.push_back(temp);
			}
		}
		for (int i = 0; i < word.length() + 1; i++) {
			for (char c = 'a'; c <= 'z'; c++) {
				temp = word.substr(0, i) + c + word.substr(i);
				result.push_back(temp);
			}
		}
		return result;
	}

	/*code for the implementation for first requirement
	  creating a trie data structure by reading the file 
	  and reading all the  contents in file  tobespellchecked
	  and if there are any misspelled words suggest 10 words 
	  for them
	  */
	void requirementone()
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
		std::cout << "\nreading the TobeSpellChecked.txt to find the misspelled words\n";
		std::ifstream file("../TobeSpellChecked.txt");
		std::string str;
		std::vector<std::string> read;
		std::vector<std::string> misspelled;
		std::string rempunc;
		std::string mistake;
		char chars[] = "()-[]#=:<>/.{}',\"0123456789?+*-|!%";
		while (std::getline(file, str))
		{
			bsplit(str, " ", read);
		}

		for (int i = 0; i<read.size(); i++)
		{
			if (trie->searchWord(read[i]))
			{

			}
			else
			{
				misspelled.push_back(read[i]);
			}
		}
		//logic for removing puntuation marks
		for (int i = 0; i < misspelled.size(); i++)
		{

			rempunc = misspelled[i];

			for (unsigned int i = 0; i < strlen(chars); ++i)
			{
				rempunc.erase(std::remove(rempunc.begin(), rempunc.end(), chars[i]), rempunc.end());
			}
			misspelled[i] = rempunc;

		}
		std::vector<std::string> newmisplled;
		for (int i = 0; i < misspelled.size(); i++)
		{
			if (trie->searchWord(misspelled[i]))
			{

			}
			else
			{
				newmisplled.push_back(misspelled[i]);
			}
		}

		//logic for the suggestion of words by insertion deletion and subsituition

		for (int i = 0; i < newmisplled.size(); i++)
		{

			int count = 0;

			std::vector<std::string> suggestions;
			Queue queue;
			std::string v = newmisplled[i];

			if (v != "")
			{
				std::cout << "\nthe misspelt word is " << v;
				queue.enqueue(v);
				long size = queue.size();
				while (size > 0 && suggestions.size() < 10)
				{
					count++;
					if (count > 6000)
					{
						std::cout << "\nbelow are the few suggestions as it is taking so much time \n";
						break;
					}
					std::string s = queue.dequeue();
					std::vector<std::string> list = edits(s);
					for (int i = 0; i < list.size(); i++)
					{
						if (trie->searchWord(list[i]))
						{
							std::vector<std::string>::iterator it = find(suggestions.begin(), suggestions.end(), list[i]);
							if (it != suggestions.end())
							{

							}
							else
							{
								if (suggestions.size() < 10)
									suggestions.push_back(list[i]);
							}
						}
						else
						{
							std::string value = list[i];
							queue.enqueue(value);
						}
					}

				}

				std::cout << "\nthe corrections are\n";
				for (int i = 0; i < suggestions.size(); i++)
				{

					std::cout << suggestions[i];
					std::cout << "\n";
				}
			}
		}


	}

};