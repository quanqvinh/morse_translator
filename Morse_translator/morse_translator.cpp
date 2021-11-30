#pragma once
#include <cstring>
#include <fstream>
#include <map>
#include <string>
#include "string_supporter.cpp"
#include <iostream>
using namespace std;

class Morse_translator {
private:
	// For look up a morse code from a letter
	map< char, string > letter_to_morse =
	{
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
	// For look up a letter from a morse code
	map<string, char> morse_to_letter;

	bool is_wrong_format(string morse) {
		for (int i = 0; i < morse.length(); i++)
			if (!string_contain(".-/", morse[i]))
				return true;
		return morse.length() > 7;
	}
public:
	// Constructor
	Morse_translator() {
		// Initialize morse_to_letter with each pairs in letter_to_morse
		map<char, string>::iterator i = letter_to_morse.begin();
		while (i != letter_to_morse.end()) {
			morse_to_letter[i->second] = i->first;
			i++;
		}
	}

	// Check file is a morse file (true), text file (false)
	bool is_morse_file(string path) {
		ifstream reader(path);
		string line;
		while (getline(reader, line))
			for (int i = 0; i < line.length(); i++)
				if (!string_contain(".-/ ", line[i]))
					return false;
		return true;
	}

	string translate_to_text(string morse, int line, vector<string>& error) {
		string text = "";
		vector<string> morses = split_string(morse, " ");
		for (int i = 0; i < morses.size(); i++) {
			if (is_wrong_format(morses[i]))
			{
				text += "#";
				error.push_back("ERROR 08: Invalid Morse code \"" + morses[i] + "\" on line " + to_string(line) + " column " + to_string(i));
			}
			else if (!morse_to_letter.count(morses[i])) {
				text += "*";
				error.push_back("ERROR 08: Invalid Morse code \"" + morses[i] + "\" on line " + to_string(line) + " column " + to_string(i));
			}
			else
				text += morse_to_letter[morses[i]];
		}
		return text;
	}

	string translate_to_morse(string text, int line, vector<string>& error) {
		string morse = "";
		for (int i = 0; i < text.length(); i++) {
			char temp = text[i];
			if (temp >= 65 && temp <= 90)
				temp += 32;
			if (!letter_to_morse.count(temp)) {
				morse += "# ";
				error.push_back("ERROR 09: Unrecognized character \"" + string(1, text[i]) + "\" on line " + to_string(line) + " column " + to_string(i));
			}
			else
				morse += letter_to_morse[temp] + " ";
		}
		morse.erase(morse.end() - 1);
		return morse;
	}

	string translate_to_text_and_count(string morse, int line, vector<string>& error, int& number_word, int& number_error_word, int& number_char, int& number_error_char) {
		string text = "";
		vector<string> morses = split_string(morse, " ");
		bool new_word = true, error_word = false;
		for (int i = 0; i < morses.size(); i++) {
			if (new_word) {
				number_word++;
				new_word = false;
			}
			number_char++;

			if (is_wrong_format(morses[i])) {
				number_error_char++;
				if (!error_word) {
					error_word = true;
					number_error_word++;
				}
				text += "#";
				error.push_back("ERROR 08: Invalid Morse code \"" + morses[i] + "\" on line " + to_string(line) + " column " + to_string(i));
			}
			else if (!morse_to_letter.count(morses[i])) {
				number_error_char++;
				if (!error_word) {
					error_word = true;
					number_error_word++;
				}
				text += "*";
				error.push_back("ERROR 08: Invalid Morse code \"" + morses[i] + "\" on line " + to_string(line) + " column " + to_string(i));
			}
			else {
				char temp = morse_to_letter[morses[i]];
				text += temp;
				if (is_punctuation_marks(temp)) {
					new_word = true;
					error_word = false;
				}
			}
		}
		return text;
	}

	string translate_to_morse_and_count(string text, int line, vector<string>& error, int& number_word, int& number_error_word, int& number_char, int& number_error_char) {
		string morse = "";
		bool new_word = true, error_word = false;
		for (int i = 0; i < text.length(); i++) {
			if (new_word) {
				number_word++;
				new_word = false;
			}
			number_char++;

			char temp = text[i];
			if (temp >= 65 && temp <= 90)
				temp += 32;
			if (!letter_to_morse.count(temp)) {
				number_error_char++;
				if (!error_word) {
					error_word = true;
					number_error_word++;
				}
				morse += "# ";
				error.push_back("ERROR 09: Unrecognized character \"" + string(1, text[i]) + "\" on line " + to_string(line) + " column " + to_string(i));
			}
			else {
				morse += letter_to_morse[temp] + " ";
				if (is_punctuation_marks(temp)) {
					new_word = true;
					error_word = false;
				}
			} 
		}
		morse.erase(morse.end() - 1);
		return morse;
	}
};