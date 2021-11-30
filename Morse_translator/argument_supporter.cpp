#pragma once
#include <string>
#include "string_supporter.cpp"
#include "file_supporter.cpp"

inline bool is_an_option(string argv) {
	return argv == "-m" || argv == "-t" || argv == "-c";
}

inline bool is_missing_argument(string argv) {
	if (is_an_option(argv))
		return true;
	else if (is_valid_file_path(argv) || is_valid_file_path(argv))
		return true;
	return false;
}

inline bool is_missing_argument(string argv1, string argv2) {
	bool argv1_is_file = is_valid_file_path(argv1);
	bool argv2_is_file = is_valid_file_path(argv2);
	bool argv1_is_option = is_an_option(argv1);
	bool argv2_is_option = is_an_option(argv2);
	return (argv1_is_file && argv2_is_option) || (argv2_is_file && argv1_is_option);
}

inline bool is_missing_argument(string argv1, string argv2, string argv3) {
	bool argv1_is_option = is_an_option(argv1);
	bool argv2_is_option = is_an_option(argv2);
	bool argv3_is_option = is_an_option(argv3);

	bool argv1_is_file = is_valid_file_path(argv1);
	bool argv3_is_file = is_valid_file_path(argv3);

	if (argv1_is_option && argv2_is_option && argv3_is_file)
		return true;
	if (argv2_is_option && argv3_is_option && argv1_is_file)
		return true;
	return false;
}

inline bool is_unrecognized_command(string argv1, string argv2) {
	bool argv1_is_file = is_valid_file_path(argv1);
	bool argv2_is_file = is_valid_file_path(argv2);
	return !argv1_is_file || !argv2_is_file;
}

inline bool is_unrecognized_command(string argv1, string argv2, string argv3) {
	bool argv1_is_option = is_an_option(argv1);
	bool argv3_is_option = is_an_option(argv3);

	bool argv1_is_file = is_valid_file_path(argv1);
	bool argv2_is_file = is_valid_file_path(argv2);
	bool argv3_is_file = is_valid_file_path(argv3);

	if (argv1_is_option && argv2_is_file && argv3_is_file)
		return false;
	if (argv3_is_option && argv1_is_file && argv2_is_file)
		return false;
	return true;
}

inline bool is_unrecognized_command(string argv1, string argv2, string argv3, string argv4) {
	bool argv1_is_option = is_an_option(argv1);
	bool argv2_is_option = is_an_option(argv2);
	bool argv3_is_option = is_an_option(argv3);
	bool argv4_is_option = is_an_option(argv4);

	bool argv1_is_file = is_valid_file_path(argv1);
	bool argv2_is_file = is_valid_file_path(argv2);
	bool argv3_is_file = is_valid_file_path(argv3);
	bool argv4_is_file = is_valid_file_path(argv4);

	if (argv1_is_option && argv2_is_option && argv3_is_file && argv4_is_file) {
		if (argv1_is_option == argv2_is_option)
			return false;
		if (argv1 != "-c" && argv2 != "-c")
			return false;
	}
	if (argv3_is_option && argv4_is_option && argv1_is_file && argv2_is_file) {
		if (argv3_is_option == argv4_is_option)
			return false;
		if (argv3 != "-c" && argv4 != "-c")
			return false;
	}
	return true;
}