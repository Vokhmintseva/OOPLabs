// MiniDictionary_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../MiniDictionary/Dictionary.h"

SCENARIO("dictionary exists")
{
	system("chcp 1251");
	char param1[] = "program";
	char param2[] = "../MiniDictionary/Dictionary.txt";
	char* argv[] = {param1, param2};
	int argc = 2;
	std::map <std::string, std::string> dictionary = GetDictionaryMap(argc, argv);
	std::ostringstream output;
	WHEN("words \"dog\ncat\" given")
	{
		std::istringstream input("dog\ncat");
		Inquire(input, output, dictionary, argv[1]);
		REQUIRE(output.str() == "собака\nкот, кошка\n");

	}

	WHEN("word \"The Red Square\" given")
	{
		std::istringstream input("The Red Square");
		Inquire(input, output, dictionary, argv[1]);
		REQUIRE(output.str() == "Красная Площадь\n");
	}

	WHEN("unknown word \"orange\" given and saved in the dictionary")
	{
		std::istringstream input("orange\nапельсин\n...\nY\n");
		Inquire(input, output, dictionary, argv[1]);
		REQUIRE(output.str() == "Unknown word \"orange\". Enter translation or empty string to reject.\nThe word \"orange\" has been saved in the dictionary as \"апельсин\".\nThe dictionary has been changed. Enter Y or y to save changes or N or n not to save them\n");
	}

	WHEN("the word \"orange\" saved earlier given and found in the dictionary")
	{
		std::istringstream input("orange");
		Inquire(input, output, dictionary, argv[1]);
		REQUIRE(output.str() == "апельсин\n");
	}
}

SCENARIO("dictionary doesn't exist")
{
	system("chcp 1251");
	char param1[] = "program";
	char* argv[] = { param1 };
	int argc = 1;
	std::map <std::string, std::string> dictionary = GetDictionaryMap(argc, argv);
	std::ostringstream output;
	WHEN("words \"cat\n")
	{
		std::istringstream input("world\nмир\n...\nY\n");
		Inquire(input, output, dictionary, "../MiniDictionary/TestDictionary.txt");
		REQUIRE(output.str() == "Unknown word \"world\". Enter translation or empty string to reject.\nThe word \"world\" has been saved in the dictionary as \"мир\".\nThe dictionary has been changed. Enter Y or y to save changes or N or n not to save them\n");
	}

	/*
	WHEN("word \"The Red Square\" given")
	{
		std::istringstream input("The Red Square");
		Inquire(input, output, dictionary, argv[1]);
		REQUIRE(output.str() == "Красная Площадь\n");
	}

	WHEN("unknown word \"orange\" given and saved in the dictionary")
	{
		std::istringstream input("orange\nапельсин\n...\nY\n");
		Inquire(input, output, dictionary, argv[1]);
		REQUIRE(output.str() == "Unknown word \"orange\". Enter translation or empty string to reject.\nThe word \"orange\" has been saved in the dictionary as \"апельсин\".\nThe dictionary has been changed. Enter Y or y to save changes or N or n not to save them\n");
	}

	WHEN("the word \"orange\" saved earlier given and found in the dictionary")
	{
		std::istringstream input("orange");
		Inquire(input, output, dictionary, argv[1]);
		REQUIRE(output.str() == "апельсин\n");
	}*/
}