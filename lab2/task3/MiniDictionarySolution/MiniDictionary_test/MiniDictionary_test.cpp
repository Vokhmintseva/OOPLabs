// MiniDictionary_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../MiniDictionary/Dictionary.h"

SCENARIO("dictionary test 1")
{
	GIVEN("dictionary")
	{
		system("chcp 1251");
		Dictionary d;
		std::istringstream input;
		std::stringstream file(std::stringstream::in | std::stringstream::out);
		std::ostringstream output;
		WHEN("reading incorrect dictionary to map")
		{
			std::string vocabulary = "cat\nкошка, кот\ndog\nсобака\nweek\nнеделя\nbook\n";
			file.str(vocabulary);

			THEN("exception was thrown")
			{
				REQUIRE_THROWS_AS(ReadDictionary(d, file), std::runtime_error);
			}
		}

		WHEN("reading correct dictionary to Dictionary")
		{
			std::string vocabulary = "cat\nкошка, кот\ndog\nсобака\nweek\nнеделя\nbook\nкнига\n";
			file.str(vocabulary);
			ReadDictionary(d, file);
			THEN("the dictionary has been read correctly")
			{
				for (auto const& entry : d.Vocabulary)
				{
					output << entry.first << '\n' << entry.second << '\n';
				}
				REQUIRE(output.str() == "book\nкнига\ncat\nкошка, кот\ndog\nсобака\nweek\nнеделя\n");
			}
			AND_WHEN("translate words that are present in the dictionary") {
				input.str("book\ncat\ndog\nweek\n");
				Inquire(input, output, d);
				THEN ("all translations were found") {
					REQUIRE(output.str() == "книга\nкошка, кот\nсобака\nнеделя\n");
				}
			}
			AND_WHEN("translate word that is not present in the dictionary and saving it then") {
				input.str("city\nгород\n\n");
				Inquire(input, output, d);
				THEN("new word has been added successfully") {
					REQUIRE(output.str() == "Unknown word \"city\". Enter translation or empty string to reject.\nThe word \"city\" has been saved in the dictionary as \"город\".\n");
				}
				
				AND_WHEN("translate word that has just been added to the dictionary")
				{
					input.clear();
					input.str("city\n");
					output.str("");
					Inquire(input, output, d);
					THEN("translation found") {
						REQUIRE(output.str() == "город\n");
					}
				}
				AND_WHEN("write down dictionary with changes")
				{
					std::ostringstream file1;
					WriteDictionary(d, file1);
					THEN("dictionary was saved")
					{
						REQUIRE(file1.str() == "book\nкнига\ncat\nкошка, кот\ncity\nгород\ndog\nсобака\nweek\nнеделя\n");
					}
				}
			}

			AND_WHEN("translate word that is not present in the dictionary with no further save")
			{
				input.str("letter\n\n");
				Inquire(input, output, d);
				THEN("new word has not been added")
				{
					REQUIRE(output.str() == "Unknown word \"letter\". Enter translation or empty string to reject.\n");
					auto it = d.Vocabulary.find("letter");
					REQUIRE(it == d.Vocabulary.end());
				}
			}
		}
	}
}

TEST_CASE("get dictionary file name - name given")
{
	std::istringstream input;
	input.str("myNewDictionary");
	std::ostringstream output;
	std::string fileName = GetDictionaryFileName(input, output);
	REQUIRE(output.str() == "Enter the name of the dictionary file in format filename.txt or empty string to miss\n");
	REQUIRE(fileName == "myNewDictionary");
}

TEST_CASE("get dictionary file name - name wasn't given")
{
	std::istringstream input;
	input.str("\n");
	std::ostringstream output;
	std::string fileName = GetDictionaryFileName(input, output);
	REQUIRE(output.str() == "Enter the name of the dictionary file in format filename.txt or empty string to miss\n");
	REQUIRE(fileName == "");
}

TEST_CASE("translate words")
{
	system("chcp 1251");
	Dictionary d;
	std::istringstream file;
	std::string vocabulary = "day\nдень\nThanksgiving Day\nДень Благодарения\nJapan\nЯпония\ndoor\nдверь\n";
	file.str(vocabulary);
	ReadDictionary(d, file);
	CHECK(TranslateWord(d, "day") == "день");
	CHECK(TranslateWord(d, "Thanksgiving Day") == "День Благодарения");
	CHECK(TranslateWord(d, "Japan") == "Япония");
	CHECK(TranslateWord(d, "door") == "дверь");
}

TEST_CASE("check command line arguments")
{
	REQUIRE_THROWS_AS(CheckNumberOfArgs(3), std::invalid_argument);
	REQUIRE_THROWS_AS(CheckNumberOfArgs(4), std::invalid_argument);
	REQUIRE_THROWS_AS(CheckNumberOfArgs(5), std::invalid_argument);
	REQUIRE_NOTHROW(CheckNumberOfArgs(2));
	REQUIRE_NOTHROW(CheckNumberOfArgs(1));
}

TEST_CASE("should save dictionary")
{	
	SECTION("should save") {
		system("chcp 1251");
		std::istringstream input;
		input.str("a\n\nY\n");
		std::ostringstream output;
		REQUIRE(ShouldSaveDictionary(input, output) == true);
		REQUIRE(output.str() == "The dictionary has been changed. Enter Y or y to save changes or N or n not to save them\nEnter Y or y to save changes or N or n not to save them.\nEnter Y or y to save changes or N or n not to save them.\n");
	}
	SECTION("should not save") {
		system("chcp 1251");
		std::istringstream input;
		input.str("n\n");
		std::ostringstream output;
		REQUIRE(ShouldSaveDictionary(input, output) == false);
		REQUIRE(output.str() == "The dictionary has been changed. Enter Y or y to save changes or N or n not to save them\n");
	}
}
