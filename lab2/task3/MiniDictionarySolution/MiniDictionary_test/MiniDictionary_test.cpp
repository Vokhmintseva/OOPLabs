// MiniDictionary_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../MiniDictionary/Dictionary.h"

SCENARIO("test existing file")
{
	GIVEN("dictionary")
	{
		system("chcp 1251");
		std::map<std::string, std::string> dictionary = GetDictionaryMap("test.txt");
		std::ostringstream output;

		WHEN("giving word 'cat'")
		{
			std::istringstream input;
			bool wasFound = false;
			TranslateWord(input, output, dictionary, "cat", wasFound);

			THEN("translation found")
			{
				REQUIRE(output.str() == "кот, кошка\n");
			}
		}
		WHEN("giving word 'day'")
		{
			std::istringstream input;
			bool wasFound = false;
			TranslateWord(input, output, dictionary, "day", wasFound);

			THEN("translation found")
			{
				REQUIRE(output.str() == "день\n");
			}
		}
		WHEN("giving unknown word 'week'")
		{
			std::istringstream input("неделя");
			bool wasFound = false;
			TranslateWord(input, output, dictionary, "week", wasFound);

			THEN("translation not found")
			{
				REQUIRE(output.str() == "Unknown word \"week\". Enter translation or empty string to reject.\nThe word \"week\" has been saved in the dictionary as \"неделя\".\n");
			}
			output.str("");
			TranslateWord(input, output, dictionary, "week", wasFound);
			THEN("translation found")
			{
				REQUIRE(output.str() == "неделя\n");
			}
		}
	}
}


