#pragma once

/////////////////////////////////////////////////////////////////////////
//invertedindex.h-it contains all the functionality related to Document Retrival//
//                                                                     //
// Language:    Visual C++ 2012                                        //
// Platform:    Lenova ThinkPad E420s, Windows 7                       //
// Application: Document Retrival - ADS, Pr#3, Spring 2017             //
// Author:       repaka ramateja,            Syracuse University       //
//              (315) 395-9575, rrepaka@syr.edu                        //
// Source:  wikipedia  and stackoverflow                               //
/////////////////////////////////////////////////////////////////////////

/*
Package Operations:
==================
this package defines all the operations that are used for:
creating the inverted index by reading all the files
taking the input query word
displaying all the files that  conatin the given query word

Public Interface:
=================
invertedindex index;
index.thirdrequirement();   //demonstartes third requirement


Build Process:
==============
Required files
Hashmap.h,Hashmap.cpp,invertedindex.h

Build commands (either one)
- devenv Requirement3Hashmap.sln

Maintenance History:
====================
ver 1.0 : 13th march 2017
-first release
*/
#include"Hashmap.h"
#include<vector>
#include<string>
#include <fstream>
#include<algorithm>
#include"../Trie/Trie.h"
#include"../Queue/Queue.h"
#include"dirent.h"
#include<set>
class invertedindex
{

public:

	//function that is used to create tokens by using delimiter space
	void ffsplit(const std::string &s, std::string sep, std::vector<std::string> &read)
	{

		char* cstr = const_cast<char*>(s.c_str());
		char* current;

		current = strtok(cstr, sep.c_str());
		while (current != NULL) {
			read.push_back(current);
			current = strtok(NULL, sep.c_str());
		}


	}

	// word suggestions that are 1 character away by subsitution insertion and deletion
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

   // this logic we are using to read all the files in the given directory

		std::vector<std::string> open(std::string path) {

			DIR*    dir;
			dirent* pdir;
			std::vector<std::string> files;

			dir = opendir(path.c_str());

			while (pdir = readdir(dir)) {
				
					files.push_back(pdir->d_name);
			}

			return files;
		}

   //third requirement implementation
		void thirdrequirement()
		{
			std::cout << "\n--------------------------demonstarting  document retrival requirement------------------------>\n";
			HashMapADT map;
			std::set<std::string> unionresults;
			std::set<std::string> onlyonce;
			int count = 0;
			
			std::vector<std::string> mainprocessing;

			std::cout << "\nelements are getting loaded into the database\n";

            //note please add files that you want in the below directory 

			std::vector<std::string> dummy = open("../inputfiles/");

			dummy.erase(dummy.begin());
			dummy.erase(dummy.begin());

			std::string mainpath;

			for(int i=0;i<dummy.size();i++)
			{ 
				std::string str;
				mainpath = "../inputfiles/"+dummy[i];
				std::ifstream infile(mainpath);

				std::vector<std::string> read;

				std::vector<std::string> misspelled;

				std::string rempunc;

				std::string mistake;

				char chars[] = "()-[]#=:<>/.{}',\"0123456789?+*-|!%";

				while (std::getline(infile, str))
				{
					ffsplit(str, " ", read);
				}
				for (int i = 0; i < read.size(); i++)
				{
					rempunc = read[i];

					for (unsigned int i = 0; i < strlen(chars); ++i)
					{
						rempunc.erase(std::remove(rempunc.begin(), rempunc.end(), chars[i]), rempunc.end());
					}
					read[i] = rempunc;
				}

				read.erase(std::remove(read.begin(), read.end(), ""), read.end());



				for (int i = 0; i < read.size(); i++)
				{
					if (read[i] != "")
					{
						string str = map.find(read[i]);
						if (str != "")
						{
							std::size_t found = str.find(mainpath);
							if (found == std::string::npos)
							{
								str = str + "\n" + mainpath;
								map.insert(read[i], str);
							}
						}
						else
						{
							map.insert(read[i], mainpath);
						}
					}

				}

			}

			std::cout << "\n Elements are inserted into the hashtable\n";

			while (true)
			{
				std::cout << "\nplease enter a query word if not enter break to display intersection \n";
				std::string query;
				
				std::getline(std::cin, query);
				
				if (query == "break")
					break;

				count++;

				//creating a dictionary object to check it is valid word

				Trie* trie = new Trie();

				std::ifstream infile("../dictionary.txt");

				std::string line;

				while (std::getline(infile, line))
				{
					trie->addWord(line);
				}


				if (trie->searchWord(query))
				{
					std::cout << "\n entered word is a valid word\n";

					string str = map.find(query);

					if (str == "")
					{
						std::cout << "query word not present in invertex index\n";
					}
					else
					{
						std::cout << "\nthe query word is present in the following list of files\n";
						std::cout << str;
						std::vector<std::string> temp;
						ffsplit(str,"\n",temp);
						std::set<std::string> results;
						for (int i = 0; i < temp.size(); i++)
						{
							std::vector<std::string>::iterator it;
							onlyonce.insert(temp[i]);
							it = find(mainprocessing.begin(),mainprocessing.end(),temp[i]);
							if (it != mainprocessing.end())
							{
								results.insert(temp[i]);
							}
							else
							{
								mainprocessing.push_back(temp[i]);
							}
						}

						unionresults = results;
					}

				}

				else
				{
					std::cout << "\nentered word is not a valid word\n";

					char chars[] = "()-[]#=:<>/.{}',\"0123456789?+*-|!%";

					for (unsigned int i = 0; i < strlen(chars); ++i)
					{
						query.erase(std::remove(query.begin(), query.end(), chars[i]), query.end());
					}

					std::cout << "\n--------the misspelt word  after all  puntuations if present-----------> " << query;

					int count = 0;
					std::vector<std::string> suggestions;
					Queue queue;
					if (query != "")
					{
						queue.enqueue(query);
						long size = queue.size();

						while (size > 0 && suggestions.size() < 10)
						{

							count++;
							if (count > 5000)
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

						std::cout << "\nreplacing the query word with the first suggestion of spell checker\n";
						query = suggestions[0];

						std::cout << "\nnow checking it is present in the inverted index or not\n";

						string str = map.find(query);

						if (str == "")
						{
							std::cout << "\nquery word not present in inverted index\n";
						}

						else
						{

							std::cout << "\nthe query word is present in the following list of files\n";
							std::cout << str;
							std::vector<std::string> temp;
							ffsplit(str, "\n", temp);
							std::set<std::string> results;
							for (int i = 0; i < temp.size(); i++)
							{
								onlyonce.insert(temp[i]);
								std::vector<std::string>::iterator it;
								it = find(mainprocessing.begin(), mainprocessing.end(), temp[i]);
								if (it != mainprocessing.end())
								{
									results.insert(temp[i]);
								}
								else
								{
									mainprocessing.push_back(temp[i]);
								}
							}

							unionresults = results;
						}

					}

				}

			}


			std::cout << "\nintersection  of results of above queries are\n";
			if (count == 1)
			{

				for (auto f : onlyonce) {
					// use f here
					std::cout << f;
					std::cout << "\n";
				}

			}
			else
			{
				for (auto f : unionresults) {
					// use f here
					std::cout << f;
					std::cout << "\n";
				}
			}


		}

};