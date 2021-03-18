#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

std::map <std::string, std::string> GetDictionaryMap(int argc, char* argv[]);

void Inquire(std::istream& input, std::ostream& output, std::map <std::string, std::string>& dictionary, std::string fileName);
