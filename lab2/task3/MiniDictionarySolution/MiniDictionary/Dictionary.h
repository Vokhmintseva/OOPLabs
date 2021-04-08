#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

std::map <std::string, std::string> GetDictionaryMap(std::string fileName);

void Inquire(std::istream& input, std::ostream& output, std::map <std::string, std::string>& dictionary, std::string fileName);

std::string GetDictionaryFileName(std::istream& input, std::ostream& output);

void CheckNumberOfArgs(int argc);

void TranslateWord(
	std::istream& input,
	std::ostream& output,
	std::map<std::string, std::string>& dictionary,
	std::string word,
	bool& wasChanged
);

void CheckNumberOfArgs(int argc);