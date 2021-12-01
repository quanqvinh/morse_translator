/* This file contains functions supporting related-string actions */
/* ============================================================== */
#pragma once
#include <string>	// support using string functions
#include <vector>	// support using dynamical array
using namespace std;

/* Get an array of sub-strings that are seperated by a string
	e.g: split_string("My name is John", " ") => ["My", "name", "is", "John"] */
inline vector<string> split_string(string text, string seperated_string) {
	vector<string> res;		// array contains splitted string
	int p = 0;		// first position of splitted string
	int seperated_len = seperated_string.length();	// length of string using to seperate
	for (int i = 0; i < text.length(); i++) {		// loop from begin to end of string using to seperate
		if (text.substr(i, seperated_len) == seperated_string) {	// if sub-string from i-th position is string using to seperate, string from p-th to i-th is a splitted string
			if (i > p) {		// this means if length of splitted string is greater than 0
				string splitted_string = text.substr(p, i - p);	// get sub-string from p-th position with length is equal to i - p
				res.push_back(splitted_string);		// append that splitted string
			}
			p = i + seperated_len;		// set first position of next splitted string
			i += seperated_len - 1;		// skip iterate the string using for seperate
		}
	}
	if (p < text.length()) {	// this means p-th is not the finish of text => contain the final seperated string
		string splitted_string = text.substr(p);	// get sub-string from p-th position to the end
		res.push_back(splitted_string);		// append the splitted string
	}
	return res;		// return array
}


// Check whether the character <value> is in string <s>
inline bool string_contain(string s, char value) {
	for (int i = 0; i < s.length(); i++)	// loop from begin to end
		if (s[i] == value)		// if s[i](a character in s) is equal to value, value is in s
			return true;
	return false;
}

// Check whether character <c> is a punctuation mark for seperating word in text file
inline bool is_punctuation_marks(char c) {
	if (c >= '0' && c <= '9')	// if c is a number, c is not a punctuation mark
		return false;
	if (c >= 'A' && c <= 'Z')	// if c is a upper letter, c is not a punctuation mark
		return false;
	if (c >= 'a' && c <= 'z')	// if c is a lower letter, c is not a punctuation mark
		return false;
	if (c == '\'' || c == '_' || c == '@' || c == '$')	// if c is a these character, c is not a punctuation mark
		return false;
	return true;	// c is a punctuation mark
}