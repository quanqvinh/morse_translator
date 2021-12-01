
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "file_supporter.cpp"
#include "morse_translator.cpp"
#include "argument_supporter.cpp"
#include <iostream>		// get input and print output
#include <fstream>	
#include <ctime>		// get date and time
#include <windows.h>	// change text color in console

#define RED_TEXT 4
#define YELLOW_TEXT 6
#define GRAY_TEXT 8
#define WHITE_TEXT 7

// Main variable
Morse_translator tran = Morse_translator();		// use public functions in class Morse_translator by this variable
ifstream reader;		// test open and read input file
ofstream writer;		// test open or create and read output file
string input_path, output_path;		// save input file path and output file path

// Declare functions
bool is_an_option(string argv);
void print_and_save_help();
string missing_argument_error();
string unrecognized_command_error();
string file_can_not_opened_error(string filename);
string file_not_exist_error(string filename);
string amount_argument_error();
string invalid_argument_order_error();
string force_text_and_morse_at_once_error();
void override_output_file();
void translate_morse_to_text();
void translate_text_to_morse();
void translate_morse_to_text_with_statistic();
void translate_text_to_morse_with_statistic();
void print_and_save_log(int duration, string time, int number_word, int number_error_word, int number_char, int number_error_char, vector<string> error);
string get_now(string format);
string get_second(double d);
void change_text_color(int color);
void print_error_message(string message);

// Main function
int main(int argc, char* argv[])
{
	string error_message;		// assign single error messages
	switch (argc) {		// check how many arguments
	case 1: {		// if number of argument is 1. Case: morse => miss argument
		error_message = missing_argument_error();
		print_error_message(error_message);
		break;	// out switch
	}
	case 2: {		// if number of argument is 2
		if (string(argv[1]) == "-h")	// morse -h  =>  print help
			print_and_save_help();
		else if (is_missed_argument(argv[1])) {		// Case: morse -c ; morse -m ; morse <inputfile> ; ...  =>  missing argument
			error_message = missing_argument_error();
			print_error_message(error_message);
		}
		else {		// all other cases is unrecognized
			error_message = unrecognized_command_error();
			print_error_message(error_message);
		}
		break;	// out switch
	}
	case 3: {		// if number of argument is 3
		if (is_missed_argument(argv[1], argv[2])) {		// Case: morse -c <inputfile> ; morse -c -m ; ... 
			error_message = missing_argument_error();
			print_error_message(error_message);
		}
		else if (is_unrecognized_command(argv[1], argv[2])) {	// except case "morse <inputfile> <outputfile>". Remaining cases are unrecognized
			error_message = unrecognized_command_error();
			print_error_message(error_message);
		}
		else {	// recognized argument
			input_path = argv[1];
			reader = ifstream(input_path);		// open file input
			if (!reader.is_open()) {		// means if file opens unsuccessfully
				if (not_exist_file(input_path)) {		// check whether file does not exists
					error_message = file_not_exist_error(input_path);
					print_error_message(error_message);
				}
				else {		// other cases mean that file exists but it can not open
					error_message = file_can_not_opened_error(input_path);
					print_error_message(error_message);
				}
				break;
			}
			output_path = string(argv[2]);
			override_output_file();		// check whether output file exists. If yes then ask to overwrite
			writer = ofstream(output_path);		// open or create file
			if (tran.is_morse_file(input_path))		// if input file is morse file
				translate_morse_to_text();		// translate from morse to text
			else
				translate_text_to_morse();		// translate text to morse
		}
		break;	// out switch
	}
	case 4: {		// if number of argument is 4
		if (is_missed_argument(argv[1], argv[2], argv[3])) {	// Case: morse -c -m <inputfile> ; morse <inputfile> -c -m ; ... 
			error_message = missing_argument_error();
			print_error_message(error_message);
		}
		else if (is_invalid_argument_order(argv[1], argv[2], argv[3])) {	// Case: morse <inputfile> -c <outputfile> ,...
			error_message = invalid_argument_order_error();
			print_error_message(error_message);
		}
		else if (is_unrecognized_command(argv[1], argv[2], argv[3])) {	// except case "morse -m <inputfile> <outputfile>", "morse <inputfile> <outputfile> -m". Remaining cases are unrecognized
			error_message = unrecognized_command_error();
			print_error_message(error_message);
		}
		else {	// recognized argument
			string option;
			// Get option type, input path and output path ------------------------
			if (is_an_option(argv[1])) {
				input_path = argv[2];
				output_path = argv[3];
				option = argv[1];
			}
			else {
				input_path = argv[1];
				output_path = argv[2];
				option = argv[3];
			}
			// --------------------------------------------------------------------
			reader = ifstream(input_path);		// open file input
			if (!reader.is_open()) {		// means if file opens unsuccessfully
				if (not_exist_file(input_path)) {		// check whether file does not exists
					error_message = file_not_exist_error(input_path);
					print_error_message(error_message);
				}
				else {		// other cases mean that file exists but it can not open
					error_message = file_can_not_opened_error(input_path);
					print_error_message(error_message);
				}
				break;
			}
			output_path = string(output_path);
			override_output_file();		// check whether output file exists. If yes then ask to overwrite
			writer = ofstream(output_path);		// open or create file
			if (option == "-t")		// force to translate from text to morse code
				translate_text_to_morse();
			else if (option == "-m")	// force to translate from morse code to text
				translate_morse_to_text();
			else if (option == "-c") {		// print statistics of the successful conversion
				if (tran.is_morse_file(input_path))		// is morse file
					translate_morse_to_text_with_statistic();		// translate morse code to text, simultaneously count number of word and statistic
				else                                    // is text file
					translate_text_to_morse_with_statistic();		// translate text to morse code, simultaneously count number of word and statistic
			}
		}
		break;	// out switch
	}
	case 5: {		// if number of argument is 5
		if (is_invalid_argument_order(argv[1], argv[2], argv[3], argv[4])) { // Cases: morse -c <inputfile> -m <outputfile>, morse <inputfile> -t -c <outputfile>,...
			error_message = invalid_argument_order_error();
			print_error_message(error_message);
		}
		else if (is_unrecognized_command(argv[1], argv[2], argv[3], argv[4])) { // except some cases like "morse -m -c <inputfile> <outputfile>", "morse <inputfile> <outputfile> -t -c". Remaining cases are unrecognized
			error_message = unrecognized_command_error();
			print_error_message(error_message);
		}
		else {  // recognized argument
			string option;
			// Get option type, input path and output path ------------------------
			if (is_an_option(argv[1])) {
				if (force_text_and_morse_at_once(argv[1], argv[2])) {	// true if two options -t and -m are used in the same time
					error_message = force_text_and_morse_at_once_error();
					print_error_message(error_message);
					break;
				}
				option = argv[1] != "-c" ? argv[1] : argv[2];
				input_path = argv[3];
				output_path = argv[4];
			}
			else if (is_an_option(argv[4])) {
				if (force_text_and_morse_at_once(argv[3], argv[4])) {	// true if two options -t and -m are used in the same time
					error_message = force_text_and_morse_at_once_error();
					print_error_message(error_message);
					break;
				}
				option = argv[3] != "-c" ? argv[3] : argv[4];
				input_path = argv[1];
				output_path = argv[2];
			}
			// --------------------------------------------------------------------
			reader = ifstream(input_path);		// open file input
			if (!reader.is_open()) {		// means if file opens unsuccessfully
				if (not_exist_file(input_path)) {		// check whether file does not exists
					error_message = file_not_exist_error(input_path);
					print_error_message(error_message);
				}
				else {		// other cases mean that file exists but it can not open
					error_message = file_can_not_opened_error(input_path);
					print_error_message(error_message);
				}
				break;
			}
			output_path = string(output_path);
			override_output_file();		// check whether output file exists. If yes then ask to overwrite
			writer = ofstream(output_path);		// open or create file
			// Logically, recognize command must contain option -c and another option (-m or -t)
			if (option == "-t")		// force to translate from text to morse code
				translate_text_to_morse_with_statistic();	// translate text to morse code, simultaneously count number of word and statistic
			else if (option == "-m")	// force to translate from morse code to text
				translate_morse_to_text_with_statistic();	// translate morse code to text, simultaneously count number of word and statistic
		}
		break;	// out switch
	}
	default: {	// other cases is wrong argument
		error_message = amount_argument_error();
		print_error_message(error_message);
		break;	// out switch
	}
	}
	return EXIT_SUCCESS;	// end program
}

// Define function

// Print help and save into file readme.txt
void print_and_save_help() {
	string help = "";
	help += " Usage: morse <inputfile> <outputfile> [-t | -m] [-c]\n";
	help += "              [-t | -m] [-c] <inputfile> <outputfile>\n";
	help += "              -h\n";
	help += " \n";
	help += " Note for file path parameter:\n";
	help += "     <inputfile> : path of an existing input file.\n";
	help += "     <outputfile> : path of an output file, if file is not exist, program create a new file, otherwise\n";
	help += "                    overwrite that file.\n";
	help += "     * NOTE : if file path contains space, it must be enclosed in double quotes *\n";
	help += " \n";
	help += " General Options:\n";
	help += "  -h : print out the help to instruct user of the usage on the screen and save the instruction\n";
	help += "       to a file name readme.txt, override if readme.txt has already existed.\n";
	help += "  -t : force to take the input file as a text file and the output file as the Morse code one.\n";
	help += "  -m : force to take the input file as Morse code and the output file as the interpreted text file.\n";
	help += "       to a file name readme.txt, override if readme.txt has already existed.\n";
	help += "  -c : print the statistics of the successful conversion to the screen including:\n";
	help += "             + Input file name and output file name\n";
	help += "             + Time when the conversion completed (formatted as YYYY-MM-DD HH:MM:SS)\n";
	help += "             + Duration of the conversion\n";
	help += "             + Word count in input file\n";
	help += "             + Number of word have been converted successfully\n";
	help += "             + Number of work contained errors\n";
	help += "             + Total number of characters in input file\n";
	help += "             + Number of characters have been converted\n";
	help += "             + Number of characters cannot be converted\n";
	help += "       and save these informations in a log file in with name <inputfile>_<outputfile>_<date>_<time>.log\n";
	cout << help;		// Print help
	ofstream readme("readme.txt");		// create file readme.txt to write
	readme << help;		// write help to file
	readme.close();		// close file to save data
}

// Self-defined error-----------------------------------------------------------
// Get error message of missing argument
string missing_argument_error() {
	return "ERROR 01: Missing arguments. Type \"morse -h\" for help.\n";
}

// Get error message of unrecognized command
string unrecognized_command_error() {
	return "ERROR 02: Unknown command. Type \"morse -h\" for help.\n";
}

// Get error message that file can not open
string file_can_not_opened_error(string filename) {
	return "ERROR 03: \"" + filename + "\" could not be opened.\n";
}

// Get error message that file does not exist
string file_not_exist_error(string filename) {
	return "ERROR 04: \"" + filename + "\" does not exists.\n";
}

// Get error message that amount of arguments is more than 4
string amount_argument_error() {
	return "ERROR 05: Amount of arguments should not be more than 4. Type \"morse -h\" for help.\n";
}

// Get error message that the order of arguments is invalid
string invalid_argument_order_error() {
	return "ERROR 06: The order of arguments is invalid. Type \"morse -h\" for help.\n";
}

// Get 
string force_text_and_morse_at_once_error() {
	return "ERROR 09: -t and -m can not be used at once.\n";
}
// -----------------------------------------------------------------------------

// Check whether output file exists. If yes, ask to overwrite it or not
void override_output_file() {
	ifstream test(output_path);		// open file to read (check file exists)
	if (test.is_open()) {		// if file is opened (file exists)
		change_text_color(GRAY_TEXT);
		cout << " -----------------------------------------------------------------------";
		change_text_color(YELLOW_TEXT);
		cout << "\n WARNING: FILENAME already exists. Do you wish to overwrite (y, n)? ";
		string choose;
		cin >> choose;	// enter "y" (yes) or other texts (no)
		change_text_color(GRAY_TEXT);
		cout << " -----------------------------------------------------------------------\n";
		change_text_color(WHITE_TEXT);
		if (choose != "y")	// if not "y" => exit program
			exit(EXIT_SUCCESS);
	}
}

// Translate morse code to text and write to output file
void translate_morse_to_text() {
	string line_content;	// store text of a line, translate_text: 
	string translated_text;	// store translated text of a line
	vector<string> error;	// array stores all errors in translating time
	int line_index = 0;		// store index of line in input file
	int number_line = count_line_in_file(input_path);	// store amount of line in input file

	// Read each line responsively, but don't read the last line
	while (line_index < number_line - 1) {
		getline(reader, line_content);	// read next line 
		translated_text = tran.translate_to_text(line_content, line_index + 1, error);	// translate line (morse code) to text, error will be added to "error" array
		writer << translated_text << endl;	// write into file
		line_index++;	// increase index of line
	}

	getline(reader, line_content);	// read the last line if file
	translated_text = tran.get_brief(line_content);	// get the brief of morse code (last line)
	if (translated_text == "")	// if not contain brief
		translated_text = tran.translate_to_text(line_content, line_index + 1, error);	// translate line to text like above
	writer << translated_text;	// write translated text of last line into output file
	writer.close();		// close file to save data

	// Print errors while translating in console
	change_text_color(RED_TEXT);
	for (int i = 0; i < error.size(); i++)
		cout << error[i] << endl;
	change_text_color(WHITE_TEXT);
}

void translate_text_to_morse() {
	string line_content;	// store text of a line, translate_text: 
	string translated_text;	// store translated text of a line
	vector<string> error;	// array stores all errors in translating time
	int line_index = 0;		// store index of line in input file
	int number_line = count_line_in_file(input_path);	// store amount of line in input file

	// Read each line responsively, but don't read the last line
	while (line_index < number_line - 1) {
		getline(reader, line_content);	// read next line 
		translated_text = tran.translate_to_morse(line_content, line_index + 1, error);	// translate line (text) to morse code, error will be added to "error" array
		writer << translated_text << endl;	// write into file
		line_index++;	// increase index of line
	}

	getline(reader, line_content);	// read the last line if file
	translated_text = tran.get_brief_morse(line_content);	// get the morse code of brief (last line)
	if (translated_text == "")	// if not contain brief
		translated_text = tran.translate_to_morse(line_content, line_index + 1, error);	// translate line to morse code like above
	writer << translated_text;	// write translated text of last line into output file
	writer.close();		// close file to save data

	// Print errors while translating in console
	change_text_color(RED_TEXT);
	for (int i = 0; i < error.size(); i++)
		cout << error[i] << endl;
	change_text_color(WHITE_TEXT);
}

void translate_morse_to_text_with_statistic() {
	int line_index = 0;		// store index of line in input file
	int number_line = count_line_in_file(input_path);	// store amount of line in input file
	int number_word = 0;		// store amount of word in input file
	int number_error_word = 0;	// store amount of error word in input file
	int number_char = 0;		// store amount of number character in input file
	int number_error_char = 0;	// store amount of error character in input file
	string line_content;		// store text of a line, translate_text: 
	string translated_text;		// store translated text of a line
	vector<string> error;	// array stores all errors in translating time
	clock_t start, end;		// store the time

	start = clock();	// get start translating time
	// Read each line responsively, but don't read the last line
	while (line_index < number_line - 1) {
		getline(reader, line_content);	// read next line 
		// translate line (morse code) to text, error will be added to "error" array, count the number word, error word, characrter, error character
		translated_text = tran.translate_to_text_and_count(line_content, line_index + 1, error, number_word, number_error_word, number_char, number_error_char);
		writer << translated_text << endl;	// write into output file
		line_index++;	// increase index of line
	}

	getline(reader, line_content);	// read the last line if file
	translated_text = tran.get_brief(line_content);	// get the brief of morse code (last line)
	if (translated_text == "")	// if not contain brief
		// Translate like above
		translated_text = tran.translate_to_text_and_count(line_content, line_index + 1, error, number_word, number_error_word, number_char, number_error_char);
	else
		number_word++;
	writer << translated_text;	// write in output file
	writer.close();		//  close to save data
	end = clock();		// get end translating time

	// Print and save log
	print_and_save_log(int(end - start), get_now("%Y-%b-%d %H:%M:%S"), number_word, number_error_word, number_char, number_error_char, error);
}

void translate_text_to_morse_with_statistic() {
	int line_index = 0;		// store index of line in input file
	int number_line = count_line_in_file(input_path);	// store amount of line in input file
	int number_word = 0;		// store amount of word in input file
	int number_error_word = 0;	// store amount of error word in input file
	int number_char = 0;		// store amount of number character in input file
	int number_error_char = 0;	// store amount of error character in input file
	string line_content;		// store text of a line, translate_text: 
	string translated_text;		// store translated text of a line
	vector<string> error;	// array stores all errors in translating time
	clock_t start, end;		// store the time

	start = clock();	// get start translating time
	// Read each line responsively, but don't read the last line
	while (line_index < number_line - 1) {
		getline(reader, line_content);	// read next line 
		// translate line (text) to morse code, error will be added to "error" array, count the number word, error word, characrter, error character
		translated_text = tran.translate_to_morse_and_count(line_content, line_index + 1, error, number_word, number_error_word, number_char, number_error_char);
		writer << translated_text << endl;	// write into output file
		line_index++;	// increase index of line
	}

	getline(reader, line_content);	// read the last line if file
	translated_text = tran.get_brief_morse(line_content);	// get the morse code of brief (last line)
	if (translated_text == "")	// if not contain brief
		// Translate like above
		translated_text = tran.translate_to_morse_and_count(line_content, line_index + 1, error, number_word, number_error_word, number_char, number_error_char);
	else
		number_word++;
	writer << translated_text;	// write in output file
	writer.close();		//  close to save data
	end = clock();		// get end translating time

	// Print and save log
	print_and_save_log(int(end - start), get_now("%Y-%b-%d %H:%M:%S"), number_word, number_error_word, number_char, number_error_char, error);
}

// Print and save log file
void print_and_save_log(int duration, string time, int number_word, int number_error_word, int number_char, int number_error_char, vector<string> errors) {
	string log = "";
	string inputfile = get_file_name(input_path), outputfile = get_file_name(output_path);
	log += " Input file: " + inputfile + "\n";
	log += " Output file: " + outputfile + "\n";
	log += " Time complete: " + time + "\n";
	log += " Duration [seconds]: " + get_second(duration / 1000.0) + "\n";
	log += " Word count in input file: " + to_string(number_word) + "\n";
	log += " Word converted: " + to_string(number_word - number_error_word) + "\n";
	log += " Word with errors: " + to_string(number_error_word) + "\n";
	log += " Total number of characters: " + to_string(number_char) + "\n";
	log += " Number of characters have been converted: " + to_string(number_char - number_error_char) + "\n";
	log += " Number of characters are NOT converted: " + to_string(number_error_char) + "\n";
	change_text_color(WHITE_TEXT);
	cout << log;	// print statistics of conversion
	if (errors.size() > 0) {
		string line = " =======================================================================\n";
		change_text_color(GRAY_TEXT);
		cout << line;
		log += line;

		change_text_color(RED_TEXT);
		for (int i = 0; i < errors.size(); i++) {
			log += errors[i] + "\n";
			cout << errors[i] + "\n";	// Print errors while translating
		}
		change_text_color(WHITE_TEXT);
	}

	string inputname, outputname;
	// Get input file name
	if (inputfile.find(".") < inputfile.length())
		inputname = inputfile.substr(0, inputfile.find("."));
	else
		inputname = inputfile;
	// Get output file name
	if (outputfile.find(".") < outputfile.length())
		outputname = outputfile.substr(0, outputfile.find("."));
	else
		outputname = outputfile;
	// Get log file name
	string log_path = inputname + "_" + outputname + "_" + get_now("%Y%m%d_%H%M%S") + ".log";

	ofstream log_writer(log_path);	// create log file to write
	log_writer << log;	// write statistic into log file
	log_writer.close();	// close file to save data
}

// Get time with any format
string get_now(string format) {
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, format.c_str(), timeinfo);
	return string(buffer);
}

// Convert second (in double) to second (in string) with milisecond precision (3 number behind decimal point)
string get_second(double d) {
	string s = to_string(d);
	int p = s.find('.');
	if (p >= s.length())
		return s + ".000";
	if (s.length() - 1 - p <= 3)
		return s + string(3 - s.length() + 1 + p, '0');
	if (s[p + 4] >= '5')
		s[p + 3]++;
	return s.substr(0, p + 4);
}

// Change text color
void change_text_color(int color) {
	HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);
	SetConsoleTextAttribute(hConsole, color);
}

// Print error message in red color
void print_error_message(string message) {
	change_text_color(RED_TEXT);
	cout << message;
	change_text_color(WHITE_TEXT);
}