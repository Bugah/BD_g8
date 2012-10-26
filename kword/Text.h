/* ----------------------------------------------------------------------------
 * Title: Text.h --------------------------------------------------------------
 * Author: andre --------------------------------------------------------------
 * Created on: Oct 23, 2012 ---------------------------------------------------
 * Last Changed on: Oct 25, 2012 ----------------------------------------------
 * ----------------------------------------------------------------------------
 * ------------------------------------------------------------------------- */

#ifndef TEXT_H_
#define TEXT_H_

#include <iostream>

/* String */
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// Alphabet definition
const string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

/*---------------------------------------------------------------------------*/
/* Class Definition */
class Text {
private:
    vector<string> txt; // Vector with all the words
    size_t size;        // Vector size

    void create(string);	// Creates a Text Object
public:
    // Methods
    void printTxt();	// Prints all the words on the text
    void add(string str)	{this->size++;	this->txt.push_back(str);}

    char getLetterAt(size_t i, int l)   {return this->txt[i].at(l);}
/*---------------------------------------------------------------------------*/
    string getTxt();
    string getIWord(size_t i)   {return this->txt.at(i);}

    size_t find_first_of(string word) {return this->find_first_of(word, 0);}
    size_t find_first_of(string, size_t);

    Text startingWith(char);      // All words starting with alpha
    Text copy(size_t, size_t);	// Subtext
    Text until(string);    // All words until the "word" one
    Text until(size_t);     // All words until "ind" one
    Text allWith(char);   // All words with alpha char
    Text exceptWith(char);      // All words without alpha char

    // Constructor
    Text(string str) {create(str);}
    Text() {this->size=0;};

    // Overwriting operator
    void operator= (Text);
    void operator= (string param) {this->create(param);}
    void operator+= (Text param) {*this = *this + param;}
    void operator+= (string param) {*this = *this + param;}
    void operator-= (Text param) {*this = *this - param;}
    void operator-= (string param) {*this = *this - param;}
    Text operator+ (Text);
    Text operator+ (string);
    Text operator- (Text);
    Text operator- (string);

};
#endif /* TEXT_H_ */
