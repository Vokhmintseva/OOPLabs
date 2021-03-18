// MiniDictionary.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "Dictionary.h"

int main(int argc, char* argv[])
{
	system("chcp 1251");
	try
	{
		std::map <std::string, std::string> dictionary = GetDictionaryMap(argc, argv);
		std::string fileName = argc == 1 ? "Dictionary.txt" : argv[1];
		Inquire(std::cin, std::cout, dictionary, fileName);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";
		return 1;
	}
}