#pragma once
#include <string>
#include <vector>
using namespace std;

inline vector<string> split_string(string text, string seperated_string) {
	vector<string> res;
	int p = 0, seperated_len = seperated_string.length();
	for (int i = 0; i < text.length(); i++) {
		if (text.substr(i, seperated_len) == seperated_string) { 
			if (i > p)
				res.push_back(text.substr(p, i - p));
			p = i + seperated_len;
			i += seperated_len - 1;
		}
	}
	if (p < text.length())
		res.push_back(text.substr(p));
	return res;
}

inline bool string_contain(string s, char value) {
	for (int i = 0; i < s.length(); i++)
		if (s[i] == value)
			return true;
	return false;
}

inline bool is_punctuation_marks(char c) {
	if (c >= '0' && c <= '9')
		return false;
	if (c >= 'A' && c <= 'Z')
		return false;
	if (c >= 'a' && c <= 'z')
		return false;
	if (c == '\'' || c == '_' || c == '@' || c == '$')
		return false;
	return true;
}