/* ----------------------------------------------------------------------------
 * Title: Text.h --------------------------------------------------------------
 * Author: andre --------------------------------------------------------------
 * Created on: Oct 23, 2012 ---------------------------------------------------
 * Last Changed on: Oct 25, 2012 ----------------------------------------------
 * ----------------------------------------------------------------------------
 * ------------------------------------------------------------------------- */

#include "Text.h"

// Methods
// Add - Create a Text with the string and sums to the Text object
void Text::add(string str) {
	Text temp;
	temp.create(str);
	*this += temp;
}

/*---------------------------------------------------------------------------*/
// Create - Initializes the Text Objects with some String
void Text::create(string str) {
    string tmp(" "), peon;
    size_t first, last, size = 0;

    if(str.size() == 0)	{
    	this->size = 0;
    	return;
    }
    // Put an empty space in the begin of the String
    tmp += str;

    // Only consider the alphabet letters and numbers (any symbol beyond this is desconsider)
    first = tmp.find_first_not_of(alpha);
    while(first != string::npos) {
        last = tmp.find_first_not_of(alpha, ++first);
        peon = tmp.substr(first, (last-first));
        first = last;

        if(peon.empty())	continue;
        // 'peon' has the next word
        this->txt.push_back(peon);
        size++;
    }
    // actualizes the size of the text
    this->size = size;
}
/*---------------------------------------------------------------------------*/
// First Version //
/* Find First Of - returns the position of the first 'word'
 * occurrence from the 'i' position */
size_t Text::find_first_of(string word, size_t i) {
	for(; i<this->size; i++) {
		if(this->txt[i] == word)	return i;
	}
	return string::npos;
}
/*---------------------------------------------------------------------------*/
// Get Text - Returns one string line with all the words in the text
string Text::getTxt() {
    string tmp; size_t ind;

    for(ind=0; ind < this->txt.size()-1; ind++) {
    	tmp += this->txt[ind]; tmp += " ";
    }
    tmp += this->txt[ind];
    return tmp;
}
/*---------------------------------------------------------------------------*/
// Print Line Text - Prints all the words of the text (one word per line)
void Text::printTxt() {
    size_t i;
    for(i=0; i < this->txt.size(); i++){
        cout << this->txt[i] << endl;
    }
}
/*---------------------------------------------------------------------------*/
/* Starting With - Return an Object with
 * only the words that starts with 'letter'*/
Text Text::startingWith(char letter) {
    size_t ind; string tmp;
    Text newTxt;

    letter = tolower(letter);
    for (ind=0; ind < this->txt.size(); ind++) {
        tmp = this->txt[ind];
        if(isupper(tmp[0]))	{
        	tmp[0] = tolower(tmp[0]);
        	if(tmp[0] == letter)	{
        		tmp[0] = toupper(tmp[0]);
        		newTxt.add(tmp);
        	}
        } else if(tmp[0]==letter)	newTxt.add(tmp);
    }
    return newTxt;
}
/*---------------------------------------------------------------------------*/
Text Text::copy(size_t fst, size_t snd) {
	Text temp;

	for(;fst < snd; fst++)	temp += this->txt.at(fst);
	return temp;

}
/*---------------------------------------------------------------------------*/
// Until - Returns a Text object that has all the words until the 'word' one
Text Text::until(string word) {
	Text temp;	size_t i, ind;

	i = this->find_first_of(word);
	for (ind=0; ind <= i; ind++)	temp += this->txt[ind];
	return temp;
}

Text Text::until(size_t ind) {
	Text temp;	size_t i;

	for(i=0; i < ind; i++)	temp += this->txt.at(ind);
	return temp;
}
/*---------------------------------------------------------------------------*/
/* All With - Returns a Text object with all the words with that contains
 *  'letter' */
Text Text::allWith(char letter) {
	Text temp;	size_t i;
	string str;

	for (i=0; i<this->size; i++) {
		str = this->txt[i];
		if(str.find(letter, 0) != string::npos)	temp += str;
		else continue;
	}
	return temp;
}
/*---------------------------------------------------------------------------*/
/* Except With - Returns a Text object with all the words with that do not
 * contains 'letter' */
Text Text::exceptWith(char letter) {
	Text temp;
	temp = this->allWith(letter);
	temp = *this-temp;
	return temp;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

// Overwrites
// Operator =
void Text::operator= (Text param) {
	this->txt = param.txt;
	this->size = param.size;
}
/*---------------------------------------------------------------------------*/
// Operator +
Text Text::operator+ (Text arg) {
	Text temp;	size_t i;

	temp = *this;
	for(i=0; i<arg.size; i++) {
		temp.txt.push_back(arg.txt[i]);
		temp.size++;
	}
	return temp;
}

Text Text::operator+ (string param) {
	Text temp, aux;
	temp = *this;	aux.create(param);
	return temp+aux;
}
/*---------------------------------------------------------------------------*/
// Operator -
Text Text::operator- (Text arg) {
	Text temp;	size_t i, check;
	string hold;

	for(i=0; i<this->size; i++) {
		hold = this->txt[i];	// Take some word of *this
		check = arg.find_first_of(hold);	// Check if it's on the args
		if(check == string::npos)	temp.add(hold);	// It's not in the args
	}
	return temp;
}

Text Text::operator- (string param) {
	Text temp;
	temp = param;
	return (*this-temp);
}
/*---------------------------------------------------------------------------*/
