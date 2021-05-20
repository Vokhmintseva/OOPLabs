#include "Dictionary.h"

struct Entry
{
	std::string word;
	std::string translation;
};

void CheckNumberOfArgs(int argc)
{
	if (argc > 2)
	{
		throw std::invalid_argument("Invalid number of arguments of command line");
	}
}

void SaveDictionary(std::istream& input, std::ostream& output, Dictionary& dictionary, std::fstream& file)
{
	if (dictionary.WasChanged)
	{
		if (ShouldSaveDictionary(std::cin, std::cout))
		{
			if (dictionary.Name.empty())
			{
				dictionary.Name = GetDictionaryFileName(std::cin, std::cout);
			}
			if (!dictionary.Name.empty())
			{
				file.open(dictionary.Name, std::fstream::out);
				if (!file.is_open())
				{
					std::ofstream outputFile(dictionary.Name);
				}
				WriteDictionary(dictionary, file);
			}
		}
	}
}

bool ShouldSaveDictionary(std::istream& input, std::ostream& output)
{
	output << "The dictionary has been changed. Enter Y or y to save changes or N or n not to save them\n";
	std::string str;
	bool shouldSave = false;
	while (std::getline(input, str))
	{
		if (str == "N" || str == "n")
		{
			break;
		}
		else if (str == "Y" || str == "y")
		{
			shouldSave = true;
			break;
		}
		output << "Enter Y or y to save changes or N or n not to save them.\n";
	}
	return shouldSave;
}

void ReadDictionary(Dictionary& dictionary, std::istream& file)
{
	Entry entry;
	while (std::getline(file, entry.word))
	{
		std::getline(file, entry.translation);
		if (file.eof())
		{
			throw std::runtime_error("Incorrect data in the file");
		}
		dictionary.Vocabulary.emplace(make_pair(entry.word, entry.translation));
	}
}

std::string GetDictionaryFileName(std::istream& input, std::ostream& output)
{
	output << "Enter the name of the dictionary file in format filename.txt or empty string to miss\n";
	std::string name;
	if (std::getline(input, name))
	{
		return (!name.empty()) ? std::move(name) : "";
	}
	return "";
}

void WriteDictionary(Dictionary& dictionary, std::ostream& file)
{
	std::map<std::string, std::string>::iterator it;
	for (it = dictionary.Vocabulary.begin(); it != dictionary.Vocabulary.end(); it++)
	{
		file << it->first << "\n";
		file << it->second << "\n";
	}
}

void AddNewWord(std::istream& input, std::ostream& output, Dictionary& dictionary, const std::string& word)
{
	output << "Unknown word \"" << word << "\". Enter translation or empty string to reject." << "\n";
	std::string translation;
	if (std::getline(input, translation))
	{
		if (!translation.empty())
		{
			dictionary.WasChanged = true;
			dictionary.Vocabulary.emplace(make_pair(word, translation));
			output << "The word \"" << word << "\" has been saved in the dictionary as \"" << translation << "\".\n";
		}
	}
}

std::string TranslateWord(Dictionary& dictionary, const std::string& word)
{
	std::string translation = "";
	translation = dictionary.Vocabulary.at(word);
	return std::move(translation);
}

void Inquire(std::istream& input, std::ostream& output, Dictionary& dictionary)
{
	std::string word;
	while (std::getline(input, word))
	{
		if (word == "...")
		{
			break;
		}
		else if (!word.empty())
		{
			if (dictionary.Vocabulary.count(word) == 1)
			{
				std::string t = TranslateWord(dictionary, word);
				output << TranslateWord(dictionary, word) << '\n';
			}
			else
			{
				AddNewWord(input, output, dictionary, word);
			}
		}
	}
}
