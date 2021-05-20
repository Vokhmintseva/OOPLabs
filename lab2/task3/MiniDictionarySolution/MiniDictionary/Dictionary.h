#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using Vocabulary = std::map <std::string, std::string>;

struct Dictionary
{
	std::map<std::string, std::string> Vocabulary;
	std::string Name = "";
	bool WasChanged = false;
};

void ReadDictionary(Dictionary& dictionary, std::istream& file);

void Inquire(std::istream& input, std::ostream& output, Dictionary& dictionary);

std::string GetDictionaryFileName(std::istream& input, std::ostream& output);

void CheckNumberOfArgs(int argc);

std::string TranslateWord(Dictionary& dictionary, const std::string& word);

bool ShouldSaveDictionary(std::istream& input, std::ostream& output);

void WriteDictionary(Dictionary& dictionary, std::ostream& file);

void SaveDictionary(std::istream& input, std::ostream& output, Dictionary& dictionary, std::fstream& file);