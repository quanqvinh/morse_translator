#pragma once
//#include <direct.h>
#include <fstream>
using namespace std;

// Get the current path of cmd process
//inline string get_current_path() {
//	char* path = NULL;
//	path = _getcwd(path, 256);
//	return path;
//}

inline bool is_valid_file_path(string path) {
	ifstream test(path);
	if (test.is_open()) {
		test.close();
		return true;
	}
	else {
		test.close();
		ofstream test2(path);
		bool res = test2.is_open();
		test2.close();
		remove(path.c_str());
		return res;
	}
}

inline bool is_not_exist_file(string path) {
	ofstream test(path);
	bool res = test.is_open();
	test.close();
	remove(path.c_str());
	return res;
}

inline string get_file_name(string path) {
	for (int i = path.length() - 1; i >= 0; i--)
		if (path[i] == '\\' || path[i] == '/')
			return path.substr(i + 1);
	return path;
}