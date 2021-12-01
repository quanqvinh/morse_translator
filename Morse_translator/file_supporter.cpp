/* This file contains functions supporting related-file actions */
/* ============================================================ */
#pragma once
#include <string>		// support using string functions
#include <fstream>		// support openning file for reading or writing
using namespace std;

// Check whether file path is valid 
inline bool is_valid_file_path(string path) {
	if (path.length() == 2 && path[0] == '-')	// this means path likes an option
		return false;
	ifstream test(path);	// test file exists by openning file to read
	if (test.is_open()) {	// file exists
		test.close();		// close file to save data
		return true;
	}
	else {							// file does not exist
		ofstream test2(path);		// test whether file can be created
		bool res = test2.is_open();	// true if file can be created, false if file cannot be created because path is wrong
		test2.close();				
		remove(path.c_str());		// delete file after testing
		return res;
	}
}

// Check whether file exists
inline bool not_exist_file(string path) {
	ofstream test(path);		// open or create file if path is valid
	bool res = test.is_open();	// true if path is valid, false if path is wrong
	test.close();
	remove(path.c_str());		// delete file after testing
	return res;
}

// Get file name from a path of file
inline string get_file_name(string path) {
	/* Find the last position of character '/' or '\', 
			the string from that position to the end is the filename */
	for (int i = path.length() - 1; i >= 0; i--)	// loop from the end to the begin of string
		if (path[i] == '\\' || path[i] == '/')		// check whether path[i] is '/' or '\'
			return path.substr(i + 1);				// slice from i + 1 to the end and return
	return path;	// if the line is executed, it mean path only contains file name
}

// Get the number of lines in a file
inline int count_line_in_file(string path) {
	int count = 0;				// count number of lines
	ifstream reader(path);		// open file to read
	for (string line; getline(reader, line); count++);	// read a line and number of line + 1
	return count;
}