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
		CheckNumberOfArgs(argc);
		Dictionary dictionary;
		
		dictionary.Name = (argc == 2) ? argv[1] : GetDictionaryFileName(std::cin, std::cout);
		std::fstream file;
		if (!dictionary.Name.empty())
		{
			file.open(dictionary.Name, std::fstream::in);
			if (!file.is_open())
			{
				throw std::runtime_error("Could not open file");
			}
			ReadDictionary(dictionary, file);
			file.close();
		}

		Inquire(std::cin, std::cout, dictionary);
		
		SaveDictionary(std::cin, std::cout, dictionary, file);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << "\n";
		return 1;
	}
}