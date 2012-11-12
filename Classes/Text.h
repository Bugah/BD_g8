/* ----------------------------------------------------------------------------
 * Title: Text.h --------------------------------------------------------------
 * Author: andre --------------------------------------------------------------
 * Created on: Oct 23, 2012 ---------------------------------------------------
 * Last Changed on: Nov 11, 2012 ----------------------------------------------
 * ----------------------------------------------------------------------------
 * ------------------------------------------------------------------------- */

#ifndef TEXT_H_
#define TEXT_H_

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

// Alphabet definition
const string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

/*---------------------------------------------------------------------------*/
/* Class Definition */
class Text {
private:
    vector<string> txt; // Vector with all the words

    void create(string);	// Creates a Text Object
    void add(string str);
public:
    // Methods
    void printTxt();	// Prints all the words on the text

    size_t getSize() {return this->txt.size();}	// Getter

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
    Text random(size_t);	// Random chooses 'size_t' words

    // Constructor
    Text(string str) {create(str);}
    Text() {};

    // Overwriting operator
    void operator= (Text param) {this->txt = param.txt;}
    void operator= (string);
    void operator+= (Text param) {*this = *this + param;}
    void operator+= (string param) {*this = *this + param;}
    void operator-= (Text param) {*this = *this - param;}
    void operator-= (string param) {*this = *this - param;}
    Text operator+ (Text);
    Text operator+ (string);
    Text operator- (Text);
    Text operator- (string);

    // Friend Definition
    friend ostream& operator<<(ostream& output, const Text& obj);

};
#endif /* TEXT_H_ */
