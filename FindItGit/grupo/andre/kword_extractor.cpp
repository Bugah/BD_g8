/* Author	: Andre N. Filliettaz ------------------------------------------
   Title	: kword_extractor.cpp ------------------------------------------
   Create Date	: 05/10/2012 ---------------------------------------------------
   Last Changed	: 05/10/2012 ---------------------------------------------------
/*----------------------------------------------------------------------------*/

// Default InOut Libs
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void getWord(string, string, int);

int main(void) {
	size_t ind, last, length;
	// Dictionary and Description Files
	ifstream fdic, fdesc;
	// Strings
	string tmp, dic, desc(""), tags("");
	
	// Checking and transforming files
	// Opens the Dictionary and transform all the words in one string

	fdic.open("dictionary.txt");	fdesc.open("description.txt");
	if(fdic.is_open())	getline(fdic, dic);
	else {
		cout << "No dictionary file was found!" << endl;
		return -1;
	}
	
	// Opens the Description file passed by the parameters on the Main
	if(fdesc.is_open()) {
		// Get the first line of the file
		getline(fdesc, tmp);
		// If the description have more than one line
		while(!fdesc.eof()) 	{
			desc += " ";
			desc += tmp;
			getline(fdesc, tmp);
		}
	}
	else {
		cout << "No description file was found!" << endl;
		return -1;
	}
	fdic.close();	fdesc.close();
	
	// Put an empty space before the description
	tmp += desc;
	desc = tmp;
	
	// Now transform into the relevants tags
	ind = desc.find_first_of(" ");
	while(ind != string::npos) {
		// Gets one word of the possibles tags string
		last = desc.find_first_of(" ", ++ind);
		tmp = desc.substr(ind, (last-ind));
		
		ind = last;

		// Search for a match on the Dictionary
		// We found the word on the dictionary, so ignore it
		if(string::npos != dic.find(tmp))	continue;

		// Here, it means that this word is a Tag, so we append to the 
		// final string with the tags of the Description
		else {
			tags += tmp;
			tags += " ";
		}
		
	}

	cout << tags << endl;
	return 0;
}
// -----------------------------------------------------------------------------
