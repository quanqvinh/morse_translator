/* Define an object name Morse_translator supporting actions related to morse code */
/* =============================================================================== */
#pragma once
#include <cstring>		// support string functions
#include <fstream>		// support open, read, write,... file
#include <map>			// for using dictionary 
#include <string>		// support string functions
#include "string_supporter.cpp"	// using defined-functions in string_supporter.cpp
using namespace std;

// 
class Morse_translator {
private:
	// For look up morse code from a letter
	map<char, string> letter_to_morse = {
		// alphabet
		{'a', ".-"},
		{'b', "-..."},
		{'c', "-.-."},
		{'d', "-.."},
		{'e', "."},
		{'f', "..-."},
		{'g', "--."},
		{'h', "...."},
		{'i', ".."},
		{'j', ".---"},
		{'k', "-.-"},
		{'l', ".-.."},
		{'m', "--"},
		{'n', "-."},
		{'o', "---"},
		{'p', ".--."},
		{'q', "--.-"},
		{'r', ".-."},
		{'s', "..."},
		{'t', "-"},
		{'u', "..-"},
		{'v', "...-"},
		{'w', ".--"},
		{'x', "-..-"},
		{'y', "-.--"},
		{'z', "--.."},
		// number
		{'0', "-----"},
		{'1', ".----"},
		{'2', "..---"},
		{'3', "...--"},
		{'4', "....-"},
		{'5', "....."},
		{'6', "-...."},
		{'7', "--..."},
		{'8', "---.."},
		{'9', "----."},
		// special character
		{'.', ".-.-.-"},
		{',', "--..--"},
		{'?', "..--.."},
		{'\'', ".----."},
		{'"', ".-..-."},
		{'!', "-.-.--"},
		{'/', "-..-."},
		{'(', "-.--."},
		{')', "-.--.-"},
		{'&', ".-..."},
		{':', "---..."},
		{';', "-.-.-."},
		{'=', "-...-"},
		{'+', ".-.-."},
		{'-', "-....-"},
		{'_', "..--.-"},
		{'"', ".-..-."},
		{'$', "...-..-"},
		{'@', ".--.-."},
		{'¿', "..-.-"},
		{'¡', "--...-"},
		{' ', "/"}
	};

	// For look up letter from a morse code
	map<string, char> morse_to_letter;

	// For look up morse code of a brief
	map<string, string> brief_to_morse = {
		{"understood", "...-."},
		{"error", "........"},
		{"invitation to transmit", "-.-"},
		{"wait", ".-..."},
		{"end of work", "...-.-"},
		{"starting signal", "-.-.-"}
	};

	// For look up brief from a morse code
	map<string, string> morse_to_brief;

	// Check whether morse code is a wrong-format code
	bool is_wrong_format(string morse) {
		// If morse contains any character that is different from '.', '-', '/', it is wrong-format
		for (int i = 0; i < morse.length(); i++)
			if (!string_contain(".-/", morse[i]))	// this mean character morse[i] is not in ".-/"
				return true;		// morse contains a character that is not in ".-/"   ==> Wrong format
		// If it only contains '.', '-', '/' , it's wrong format when its length is greater then 7
		return morse.length() > 7;	// true if it's length is greater than 7
	}
public:
	// Constructor
	Morse_translator() {
		// Initialize morse_to_letter with each pairs in letter_to_morse
		map<char, string>::iterator i = letter_to_morse.begin();	// loop dictionary letter_to_morse
		while (i != letter_to_morse.end()) {
			// i->first is key (letter), i->second is value (morse code)
			morse_to_letter[i->second] = i->first;
			i++;
		}
		// Initialize morse_to_brief with each pairs in brief_to_morse
		map<string, string>::iterator j = brief_to_morse.begin();	// loop dictionary brief_to_morse
		while (j != brief_to_morse.end()) {
			// i->first is key (brief), i->second is value (morse code)
			morse_to_brief[j->second] = j->first;
			j++;
		}
	}

	// Check file is a morse file (true), text file (false)
	bool is_morse_file(string path) {
		ifstream reader(path);		// open file to read
		string line;
		// Read and check each line 
		while (getline(reader, line))	// read a line in file into "line"
			for (int i = 0; i < line.length(); i++)		// check each character in "line"
				if (!string_contain(".-/ ", line[i]))	// this mean character line[i] is not in ".-/"
					return false;		// contain a character that is not in ".-/"   ==>  is text file
		return true;		// is morse file
	}

	// Translate and return a string from morse code to text
	string translate_to_text(string morse, int line, vector<string>& error) {
		if (morse == "")	// Check if it is an empty string
			return "";
		string text = "";	// contains translated text
		vector<string> morses = split_string(morse, " ");	// split morse codes in the string and assign into an array
		for (int i = 0; i < morses.size(); i++) {		// iterate each morse code in array
			if (is_wrong_format(morses[i]))	{	// if morse code morse[i] is wrong format
				text += "#";
				error.push_back(" ERROR 07: Invalid Morse code \"" + morses[i] + "\" on line " + to_string(line) + " column " + to_string(i + 1));
			}
			else if (!morse_to_letter.count(morses[i])) {	// this mean morse code morses[i] is not in dictionary
				text += "*";
				error.push_back(" ERROR 07: Invalid Morse code \"" + morses[i] + "\" on line " + to_string(line) + " column " + to_string(i + 1));
			}
			else
				text += morse_to_letter[morses[i]];		// get letter of morse code from dictionary morse_to_letter
		}
		return text;	// return translated text
	}

	// Translate and return a morse code string from text
	string translate_to_morse(string text, int line, vector<string>& error) {
		if (text == "")		// Check if it is an empty string
			return "";
		string morse = "";	// contains translated morse code string
		for (int i = 0; i < text.length(); i++) {	// iterate each character in text
			if (text[i] >= 65 && text[i] <= 90)		// if character is an uppper letter
				text[i] += 32;		// convert into lower letter
			if (!letter_to_morse.count(text[i])) { // this mean morse code text[i] is not in dictionary
				morse += "# ";
				error.push_back(" ERROR 08: Unrecognized character \"" + string(1, text[i]) + "\" on line " + to_string(line) + " column " + to_string(i + 1));
			}
			else
				morse += letter_to_morse[text[i]] + " ";	// get morse code from dictionary letter_to_morse
		}
		morse.erase(morse.end() - 1);	// delete last space in text
		return morse;		// return translated morse code 
	}

	// Translate and return a string from morse code to text, count the number of words, error words, character, error character
	string translate_to_text_and_count(string morse, int line, vector<string>& error, int& number_word, int& number_error_word, int& number_char, int& number_error_char) {
		if (morse == "")	// Check if it is an empty string
			return "";
		string text = "";	// contains translated text
		vector<string> morses = split_string(morse, " ");	// split morse codes in the string and assign into an array
		bool new_word = true;	// is new word ( a word is end with ' ' , '.' , ';' , ',' ,...
		bool error_word = false;	// this word is error
		for (int i = 0; i < morses.size(); i++) {	// iterate each character in text
			if (new_word) {		// check new word, +1 amount of word
				number_word++;
				new_word = false;	
			}
			number_char++;		// + 1 amount of character

			if (is_wrong_format(morses[i])) {	// if morse code morse[i] is wrong format
				number_error_char++;	// + 1 amount error character
				if (!error_word) {		// if word is true (not contain error character before)
					error_word = true;	// this word is error
					number_error_word++;	// + 1 amount of error word
				}
				text += "#";
				error.push_back(" ERROR 07: Invalid Morse code \"" + morses[i] + "\" on line " + to_string(line) + " column " + to_string(i + 1));
			}
			else if (!morse_to_letter.count(morses[i])) {	// this mean morse code morses[i] is not in dictionary
				number_error_char++;	// + 1 amount error character
				if (!error_word) {		// if word is true (not contain error character before)
					error_word = true;	// this word is error
					number_error_word++;	// + 1 amount of error word
				}
				text += "*";
				error.push_back(" ERROR 07: Invalid Morse code \"" + morses[i] + "\" on line " + to_string(line) + " column " + to_string(i + 1));
			}
			else {
				char temp = morse_to_letter[morses[i]];		// get character of morse code 
				text += temp;
				if (is_punctuation_marks(temp)) {		// true if character is a punctuation marks => next character is in new word
					new_word = true;
					error_word = false;
				}
			}
		}
		return text;
	}

	// Translate and return a morse code string from text, count the number of words, error words, character, error character
	string translate_to_morse_and_count(string text, int line, vector<string>& error, int& number_word, int& number_error_word, int& number_char, int& number_error_char) {
		if (text == "")		// Check if it is an empty string
			return "";
		string morse = "";	// contains translated morse code string
		bool new_word = true;	// is new word ( a word is end with ' ' , '.' , ';' , ',' ,...
		bool error_word = false;	// this word is error
		for (int i = 0; i < text.length(); i++) {		// iterate each morse code in array
			if (new_word) {		// check new word, +1 amount of word
				number_word++;
				new_word = false;	
			}
			number_char++;		// + 1 amount of character

			char temp = text[i];
			if (temp >= 65 && temp <= 90)	// true if character is an upper character => change to lower character
				temp += 32;			// e.g: ASCII code of character 'A' is 65, ASCII code of character 'a' is 97 => + 32 to make uppercase to lowercase 
			if (!letter_to_morse.count(temp)) {		// this mean morse code temp is not in dictionary
				number_error_char++;	// + 1 amount error character
				if (!error_word) {
					error_word = true;	// this word is error
					number_error_word++;	// + 1 amount of error word
				}
				morse += "# ";
				error.push_back(" ERROR 08: Unrecognized character \"" + string(1, text[i]) + "\" on line " + to_string(line) + " column " + to_string(i + 1));
			}
			else {
				morse += letter_to_morse[temp] + " ";
				if (is_punctuation_marks(temp)) {		// true if character is a punctuation marks => next character is in new word
					new_word = true;
					error_word = false;
				}
			} 
		}
		morse.erase(morse.end() - 1);	// delete last space in text
		return morse;		// return translated morse code 
	}

	// Get brief of morse code
	string get_brief(string morse) {
		return morse_to_brief[morse];
	}

	// Get morse code of brief
	string get_brief_morse(string brief) {
		return brief_to_morse[brief];
	}
};