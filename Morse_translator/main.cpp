#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "file_supporter.cpp"
#include "morse_translator.cpp"
#include "argument_supporter.cpp"
#include <iostream>
#include <fstream>
#include <ctime>

// Main variable
Morse_translator tran = Morse_translator();
ifstream reader;
ofstream writer;
string input_path, output_path;

// Function
bool is_an_option(string argv);
void print_and_save_help();
string missing_argument_error();
string unrecognized_command_error();
string file_can_not_opened_error(string filename);
string file_not_exist_error(string filename);
string amount_argument_error();
string invalid_order_argument_error();
void override_output_file();
void translate_morse_to_text();
void translate_text_to_morse();
void translate_morse_to_text_with_log();
void translate_text_to_morse_with_log(); 
void print_and_save_log(int duration, string time, int number_word, int number_error_word, int number_char, int number_error_char);
string get_now(string format);
string get_second(double d);

// Main function
int main(int argc, char* argv[])
{
	switch (argc) {
	case 1: {
		cout << missing_argument_error();
		break;
	}
	case 2: {
		if (string(argv[1]) == "-h")
			print_and_save_help();
		else if (is_missing_argument(argv[1]))
			cout << missing_argument_error();
		else
			cout << unrecognized_command_error();
		break;
	}
	case 3: {
		if (is_missing_argument(argv[1], argv[2]))
			cout << missing_argument_error();
		else if (is_unrecognized_command(argv[1], argv[2]))
			cout << unrecognized_command_error();
		else {
			reader = ifstream(argv[1]);
			if (!reader.is_open()) {
				if (is_not_exist_file(argv[1]))
					cout << file_not_exist_error(argv[1]);
				else
					cout << file_can_not_opened_error(argv[1]);
				break;
			}
			output_path = string(argv[2]);
			override_output_file();
			writer = ofstream(argv[2]);
			if (tran.is_morse_file(argv[1]))
				translate_morse_to_text();
			else 
				translate_text_to_morse(); 
		}
		break;
	}
	case 4: {
		if (is_missing_argument(argv[1], argv[2], argv[3]))
			cout << missing_argument_error();
		else if (is_unrecognized_command(argv[1], argv[2], argv[3]))
			cout << unrecognized_command_error();
		else {
			string option;
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
			reader = ifstream(input_path);
			if (!reader.is_open()) {
				if (is_not_exist_file(input_path))
					cout << file_not_exist_error(input_path);
				else
					cout << file_can_not_opened_error(input_path);
				break;
			}
			output_path = string(output_path);
			override_output_file();
			writer = ofstream(output_path);
			if (option == "-t")
				translate_text_to_morse();
			else if (option == "-m")
				translate_morse_to_text();
			else if (option == "-c") {
				if (tran.is_morse_file(input_path))
					translate_morse_to_text_with_log();
				else
					translate_text_to_morse_with_log();
			}
		}
		break;
	}
	case 5: {
		if (is_unrecognized_command(argv[1], argv[2], argv[3], argv[4]))
			cout << unrecognized_command_error();
		else {
			string option;
			if (is_an_option(argv[1])) {
				option = argv[1] != "-c" ? argv[1] : argv[2];
				input_path = argv[3];
				output_path = argv[4];
			}
			else if (is_an_option(argv[4])) {
				option = argv[3] != "-c" ? argv[3] : argv[4];
				input_path = argv[1];
				output_path = argv[2];
			}
			reader = ifstream(input_path);
			if (!reader.is_open()) {
				if (is_not_exist_file(input_path))
					cout << file_not_exist_error(input_path);
				else
					cout << file_can_not_opened_error(input_path);
				break;
			}
			output_path = string(output_path);
			override_output_file();
			writer = ofstream(output_path);
			if (option == "-t")
				translate_text_to_morse_with_log();
			else if (option == "-m")
				translate_morse_to_text_with_log();
		}
		break;
	}
	default: {
		cout << amount_argument_error();
		break;
	}
	}
	return EXIT_SUCCESS;
}

// Define function

void print_and_save_help() {
	string help = "";
	help += "Usage: morse <inputfile> <outputfile> [-t | -m] [-c]\n";
	help += "             [-t | -m] [-c] <inputfile> <outputfile>\n";
	help += "             -h\n";
	help += "\n";
	help += "Note for file path parameter:\n";
	help += "    <inputfile>, <outputfile> : path do not have any whitespace of a file.\n";
	help += "    <inputfile> : path of an existing input file.\n";
	help += "    <outputfile> : path of an output file, if file is not exist, program create a new file, otherwise\n";
	help += "                   overwrite that file.\n";
	help += "\n";
	help += "General Options:\n";
	help += " -h : print out the help to instruct user of the usage on the screen and save the instruction\n";
	help += "      to a file name readme.txt, override if readme.txt has already existed.\n";
	help += " -t : force to take the input file as a text file and the output file as the Morse code one.\n";
	help += " -m : force to take the input file as Morse code and the output file as the interpreted text file.\n";
	help += "      to a file name readme.txt, override if readme.txt has already existed.\n";
	help += " -c : print the statistics of the successful conversion to the screen including:\n";
	help += "            + Input file name and output file name\n";
	help += "            + Time when the conversion completed (formatted as YYYY-MM-DD HH:MM:SS)\n";
	help += "            + Duration of the conversion\n";
	help += "            + Word count in input file\n";
	help += "            + Number of word have been converted successfully\n";
	help += "            + Number of work contained errors\n";
	help += "            + Total number of characters in input file\n";
	help += "            + Number of characters have been converted\n";
	help += "            + Number of characters cannot be converted\n";
	help += "      and save these informations in a log file in with name <inputfile>_<outputfile>_<date>_<time>.log\n";
	cout << help;
	ofstream readme("readme.txt");
	readme << help;
	readme.close();
}

string missing_argument_error() {
	return "ERROR 01: Missing arguments. Type \"morse -h\" for help\n";
}

string unrecognized_command_error() {
	return "ERROR 02: Unknown command. Type \"morse -h\" for help\n";
}

string file_can_not_opened_error(string filename) {
	return "ERROR 03: \"" + filename + "\" could not be opened\n";
}

string file_not_exist_error(string filename) {
	return "ERROR 04: \"" + filename + "\" does not exists\n";
}

string amount_argument_error() {
	return "ERROR 06: Amount of arguments should not be more than 4\n";
}

string invalid_order_argument_error() {
	return "ERROR 07: Maybe the order of arguments is invalid!\n";
}

void override_output_file() {
	ifstream test(output_path);
	if (test.is_open()) {
		cout << "Warning: FILENAME already exists. Do you wish to overwrite (y, n)? ";
		string choose;
		cin >> choose;
		if (choose != "y")
			exit(0);
	}
}

void translate_morse_to_text() {
	string line_content;
	getline(reader, line_content);
	int line_number = 1;
	vector<string> error;
	writer << tran.translate_to_text(line_content, line_number, error);
	while (getline(reader, line_content)) {
		line_number++;
		writer << endl << tran.translate_to_text(line_content, line_number, error);
	}
	for (int i = 0; i < error.size(); i++)
		cout << error[i] << endl;
}

void translate_text_to_morse() {
	string line_content;
	getline(reader, line_content);
	int line_number = 1;
	vector<string> error;
	writer << tran.translate_to_morse(line_content, line_number, error);
	while (getline(reader, line_content)) {
		line_number++;
		writer << endl << tran.translate_to_morse(line_content, line_number, error);
	}
	for (int i = 0; i < error.size(); i++)
		cout << error[i] << endl;
}

void translate_morse_to_text_with_log() {
	int line_number = 1, number_word = 0, number_error_word = 0, number_char = 0, number_error_char = 0;
	string line_content;
	vector<string> error;
	clock_t start, end;

	start = clock();
	getline(reader, line_content);
	writer << tran.translate_to_text_and_count(line_content, line_number, error, number_word, number_error_word, number_char, number_error_char);
	while (getline(reader, line_content)) {
		line_number++;
		writer << endl << tran.translate_to_text_and_count(line_content, line_number, error, number_word, number_error_word, number_char, number_error_char);
	}
	end = clock();

	print_and_save_log(int(end - start), get_now("%Y-%b-%d %H:%M:%S"), number_word, number_error_word, number_char, number_error_char);
	for (int i = 0; i < error.size(); i++)
		cout << error[i] << endl;
}

void translate_text_to_morse_with_log() {
	int line_number = 1, number_word = 0, number_error_word = 0, number_char = 0, number_error_char = 0;
	string line_content;
	vector<string> error;
	clock_t start, end;

	start = clock();
	getline(reader, line_content);
	writer << tran.translate_to_morse_and_count(line_content, line_number, error, number_word, number_error_word, number_char, number_error_char);
	while (getline(reader, line_content)) {
		line_number++;
		writer << endl << tran.translate_to_morse_and_count(line_content, line_number, error, number_word, number_error_word, number_char, number_error_char);
	}
	end = clock();

	print_and_save_log(int(end - start), get_now("%Y-%b-%d %H:%M:%S"), number_word, number_error_word, number_char, number_error_char);
	for (int i = 0; i < error.size(); i++)
		cout << error[i] << endl;
}

void print_and_save_log(int duration, string time, int number_word, int number_error_word, int number_char, int number_error_char) {
	string log = "";
	string inputfile = get_file_name(input_path), outputfile = get_file_name(output_path);
	log += "Input file: " + inputfile + "\n";
	log += "Output file: " + outputfile + "\n";
	log += "Time complete: " + time + "\n";
	log += "Duration [seconds]: " + get_second(duration / 1000.0) + "\n";
	log += "Word count in input file: " + to_string(number_word) + "\n";
	log += "Word converted: " + to_string(number_word - number_error_word) + "\n";
	log += "Word with errors: " + to_string(number_error_word) + "\n";
	log += "Total number of characters: " + to_string(number_char) + "\n";
	log += "Number of characters have been converted: " + to_string(number_char - number_error_char) + "\n";
	log += "Number of characters are NOT converted: " + to_string(number_error_char) + "\n";
	cout << log;

	string inputname, outputname;
	if (inputfile.find(".") < inputfile.length())
		inputname = inputfile.substr(0, inputfile.find("."));
	else
		inputname = inputfile;
	if (outputfile.find(".") < outputfile.length())
		outputname = outputfile.substr(0, outputfile.find("."));
	else
		outputname = outputfile;
	string log_path = output_path.substr(0, output_path.length() - outputfile.length()) 
		+ inputname + "_" + outputname + "_" + get_now("%Y%m%d_%H%M%S") + ".log";

	cout << log_path << endl;
	ofstream log_writer(log_path);
	log_writer << log;
	log_writer.close();
}

string get_now(string format) {
	time_t rawtime;
	struct tm* timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, format.c_str(), timeinfo);
	return string(buffer);
}

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