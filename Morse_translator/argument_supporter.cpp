/* This file contains functions supporting related-argument actions */
/* ================================================================ */
#pragma once
#include <string>					// support using string functions
#include "string_supporter.cpp"		// using defined-functions from string_supporter.cpp
#include "file_supporter.cpp"		// using defined-functions from file_supporter.cpp

// Check whether argument is an option
inline bool is_an_option(string argv) {
	return argv == "-m" || argv == "-t" || argv == "-c";
}

/* Check one-argument command type is missed argument.
* E.g: morse -m => missed argument is <inputfile>, <outputfile>
*      morse <inputfile> => missed argument is <outputfile>
*/
inline bool is_missed_argument(string argv) { 
	if (is_an_option(argv))				// if argv is option => miss argument
		return true;
	else if (is_valid_file_path(argv))	// if argv is a valid file (inputfile or outputfile) => miss argument
		return true;
	return false;	// not miss argument
}

/* Check two-argument command type is missed arguments.
* E.g: morse -m <inputfile> => missed argument is <outputfile>
*      morse -m -c => missed argument is <inputfile>, <outputfile>
*/
inline bool is_missed_argument(string argv1, string argv2) {
	bool argv1_is_file = is_valid_file_path(argv1);
	bool argv2_is_file = is_valid_file_path(argv2);
	bool argv1_is_option = is_an_option(argv1);
	bool argv2_is_option = is_an_option(argv2);

	if (argv1_is_option && argv2_is_option) {	// In case: morse -c -m,...
		if (argv1 == argv2)						// In case: morse -m -m <inputfile>,...
			return false;
		if (argv1 != "-c" && argv2 != "-c")
			return false;
		return true;
	}
	if (argv1_is_file && argv2_is_option)		// In case: morse <inputfile> -m,...
		return true;
	if (argv1_is_option && argv2_is_file)		// In case: morse -m <inputfile>,...
		return true;
	return false;	// not miss argument
}

/* Check three-argument command type is missed arguments.
* E.g: morse -m -c <inputfile> => missed argument is <outputfile>
*      morse <inputfile> -m -c => missed argument is <outputfile>
*/
inline bool is_missed_argument(string argv1, string argv2, string argv3) {
	bool argv1_is_option = is_an_option(argv1);
	bool argv2_is_option = is_an_option(argv2);
	bool argv3_is_option = is_an_option(argv3);

	bool argv1_is_file = is_valid_file_path(argv1);
	bool argv3_is_file = is_valid_file_path(argv3);

	if (argv1_is_option && argv2_is_option && argv3_is_file) {	// In case: morse -c -m <inputfile>,...
		if (argv1 == argv2)						// In case: morse -m -m <inputfile>,...
			return false;
		if (argv1 != "-c" && argv2 != "-c")		// In case: morse -t -m <inputfile>,...
			return false;
		return true;
	}
	if (argv1_is_file && argv2_is_option && argv3_is_option) {	// In case: morse <inputfile> -c -m,...
		if (argv2 == argv3)						// In case: morse <inputfile> -m -m,...
			return false;
		if (argv2 != "-c" && argv3 != "-c")		// In case: morse <inputfile> -t -m,...
			return false;
		return true;
	}
	return false;	// not miss argument
}

// Check whether arguments order of three-argument command type is invalid.
inline bool is_invalid_argument_order(string argv1, string argv2, string argv3) {
	bool argv2_is_option = is_an_option(argv2);

	bool argv1_is_file = is_valid_file_path(argv1);
	bool argv3_is_file = is_valid_file_path(argv3);

	if (argv1_is_file && argv2_is_option && argv3_is_file)	// In case: morse <inputfile> -m <outputfile>,...
		return true;
	return false;	// argument order is valid
}

// Check whether arguments order of four-argument command type is invalid.
inline bool is_invalid_argument_order(string argv1, string argv2, string argv3, string argv4) {
	bool argv1_is_option = is_an_option(argv1);
	bool argv2_is_option = is_an_option(argv2);
	bool argv3_is_option = is_an_option(argv3);
	bool argv4_is_option = is_an_option(argv4);

	bool argv1_is_file = is_valid_file_path(argv1);
	bool argv2_is_file = is_valid_file_path(argv2);
	bool argv3_is_file = is_valid_file_path(argv3);
	bool argv4_is_file = is_valid_file_path(argv4);

	if (argv1_is_option && argv2_is_file && argv3_is_option && argv4_is_file) {	// In case: morse -m <inputfile> -c <outputfile>,...
		if (argv1 == argv3)	
			return false;
		if (argv1 != "-c" && argv3 != "-c")
			return false;
		return true;
	}
	if (argv1_is_file && argv2_is_option && argv3_is_file && argv4_is_option) {	// In case: morse <inputfile> -c <outputfile> -m,...
		if (argv2 == argv4)
			return false;
		if (argv2 != "-c" && argv4 != "-c")
			return false;
		return true;
	}
	if (argv1_is_option && argv2_is_file && argv3_is_file && argv4_is_option) {	// In case: morse -m <inputfile> <outputfile> -c,...
		if (argv1 == argv4)
			return false;
		if (argv1 != "-c" && argv4 != "-c")
			return false;
		return true;
	}
	if (argv1_is_file && argv2_is_option && argv3_is_option && argv4_is_file) {	// In case: morse <inputfile> -m -c <outputfile>,...
		if (argv2 == argv3)
			return false;
		if (argv2 != "-c" && argv3 != "-c")
			return false;
		return true;
	}
	return false;
}

// Check whether two-argument command type is unrecognized
inline bool is_unrecognized_command(string argv1, string argv2) {
	bool argv1_is_file = is_valid_file_path(argv1);
	bool argv2_is_file = is_valid_file_path(argv2);
	return !argv1_is_file || !argv2_is_file;	// this means one of argv1 and argv2 is an invalid file
}

// Check whether three-argument command type is unrecognized
inline bool is_unrecognized_command(string argv1, string argv2, string argv3) {
	bool argv1_is_option = is_an_option(argv1);
	bool argv3_is_option = is_an_option(argv3);

	bool argv1_is_file = is_valid_file_path(argv1);
	bool argv2_is_file = is_valid_file_path(argv2);
	bool argv3_is_file = is_valid_file_path(argv3);

	// Return false if command is proper
	if (argv1_is_option && argv2_is_file && argv3_is_file)		// In case: morse -m <inputfile> <outputfile>,...
		return false;
	if (argv1_is_file && argv2_is_file && argv3_is_option)		// In case: morse <inputfile> <outputfile> -m,...
		return false;
	return true;	// is unregconized command
}

// Check whether four-argument command type is unrecognized
inline bool is_unrecognized_command(string argv1, string argv2, string argv3, string argv4) {
	bool argv1_is_option = is_an_option(argv1);
	bool argv2_is_option = is_an_option(argv2);
	bool argv3_is_option = is_an_option(argv3);
	bool argv4_is_option = is_an_option(argv4);

	bool argv1_is_file = is_valid_file_path(argv1);
	bool argv2_is_file = is_valid_file_path(argv2);
	bool argv3_is_file = is_valid_file_path(argv3);
	bool argv4_is_file = is_valid_file_path(argv4);

	if (argv1_is_option && argv2_is_option && argv3_is_file && argv4_is_file) {	// In caase: morse -m -c <inputfile> <outputfile>,...
		if (argv1 == argv2)
			return true;
		if (argv1 != "-c" && argv2 != "-c")
			return false;
		return false;
	}
	if (argv3_is_option && argv4_is_option && argv1_is_file && argv2_is_file) {	// In caase: morse <inputfile> <outputfile> -m -c,...
		if (argv3 == argv4)
			return true;
		if (argv3 != "-c" && argv4 != "-c")
			return false;
		return false;
	}
	return true;
}

// Check whether two options -t and -m are used in the same time
inline bool force_text_and_morse_at_once(string argv1, string argv2) {
	if (argv1 != "-c" && argv2 != "-c")
		return true;
	return false;
}