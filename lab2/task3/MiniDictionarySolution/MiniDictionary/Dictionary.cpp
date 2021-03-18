#include "Dictionary.h"

struct Entry
{
	std::string word;
	std::string translation;
};

std::map <std::string, std::string> GetDictionaryMap(int argc, char* argv[])
{
	if (argc > 2)
	{
		throw std::invalid_argument("Invalid number of arguments of command line");
	}
	std::map <std::string, std::string> dictionary;
	if (argc == 2)
	{
		std::ifstream file(argv[1]);
		if (!file.is_open())
		{
			throw std::runtime_error("Could not open file");
		}
		Entry entry;
		while (std::getline(file, entry.word))
		{
			std::getline(file, entry.translation);
			if (file.bad())
			{
				throw std::runtime_error("Incorrect data in the file");
			}
			dictionary.insert(make_pair(entry.word, entry.translation));
		}
	}
	return dictionary;
}

void EndUpProgram(std::istream& input, std::ostream& output, std::map <std::string, std::string>& dictionary, std::string fileName)
{
	output << "The dictionary has been changed. Enter Y or y to save changes or N or n not to save them" << "\n";
	std::string str;
	while (std::getline(input, str))
	{
		if (str == "N" || str == "n")
		{
			break;
		}
		else if (str == "Y" || str == "y")
		{
			std::ofstream outputFile;
			outputFile.open(fileName);
			if (!outputFile.is_open())
			{
				std::ofstream outputFile(fileName);
			}
			std::map <std::string, std::string> ::iterator it;
			for (it = dictionary.begin(); it != dictionary.end(); it++)
			{
				outputFile << it->first << "\n";
				outputFile << it->second << "\n";
			}
			break;
		}
	}
}

void handleNewWord(std::istream& input, std::ostream& output, std::map <std::string, std::string>& dictionary, std::string word, bool& wasChanged)
{
	output << "Unknown word \"" << word << "\". Enter translation or empty string to reject." << "\n";
	std::string translation;
	std::getline(input, translation);
	if (!translation.empty())
	{
		wasChanged = true;
		dictionary.insert(make_pair(word, translation));
		output << "The word \"" << word << "\" has been saved in the dictionary as \"" << translation << "\".\n";
	}
}

void Inquire(std::istream& input, std::ostream& output, std::map <std::string, std::string>& dictionary, std::string fileName)
{
	std::string word;
	bool wasChanged = false;
	while (std::getline(input, word))
	{
		if (word == "...")
		{
			if (wasChanged)
			{
				EndUpProgram(input, output, dictionary, fileName);
			}
			break;
		}
		else if (!word.empty())
		{
			std::map <std::string, std::string>::iterator it;
			it = dictionary.find(word);
			if (it == dictionary.end())
			{
				handleNewWord(input, output, dictionary, word, wasChanged);
			}
			else
			{
				output << it->second << "\n";
			}
		}
	}
}