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

void ReadDictionaryFromFile(std::map<std::string, std::string> &dictionary, std::ifstream &file)
{
	Entry entry;
	while (std::getline(file, entry.word))
	{
		std::getline(file, entry.translation);
		if (file.eof())
		{
			throw std::runtime_error("Incorrect data in the file");
		}
		dictionary.insert(make_pair(entry.word, entry.translation));
	}
}

std::map <std::string, std::string> GetDictionaryMap(std::string fileName)
{
	std::map<std::string, std::string> dictionary;
	if (!fileName.empty())
	{
		std::ifstream file(fileName);
		if (!file.is_open())
		{
			throw std::runtime_error("Could not open file");
		}
		ReadDictionaryFromFile(dictionary, file);
	}
	return dictionary;
}

std::string GetDictionaryFileName(std::istream& input, std::ostream& output)
{
	output << "Enter the name of the dictionary file. Enter empty string to miss\n";
	std::string name;
	if (std::getline(input, name))
	{
		return (!name.empty()) ? name : "";
	}
	return "";
}

void SaveDictionaryToFile(std::map<std::string, std::string>& dictionary, std::string fileName)
{
	std::ofstream outputFile;
	outputFile.open(fileName);
	if (!outputFile.is_open())
	{
		std::ofstream outputFile(fileName);
	}
	std::map<std::string, std::string>::iterator it;
	for (it = dictionary.begin(); it != dictionary.end(); it++)
	{
		outputFile << it->first << "\n";
		outputFile << it->second << "\n";
	}
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
			if (fileName.empty())
			{
				fileName = GetDictionaryFileName(input, output);
				if (fileName.empty())
				{
					break;
				}
			}
			SaveDictionaryToFile(dictionary, fileName);
			break;
		}
		output << "The dictionary has been changed. Enter Y or y to save changes or N or n not to save them\n";
	}
}

void AddNewWord(
	std::istream& input,
	std::ostream& output,
	std::map <std::string, std::string>& dictionary,
	std::string word,
	bool& wasChanged
)
{
	output << "Unknown word \"" << word << "\". Enter translation or empty string to reject." << "\n";
	std::string translation;
	if (std::getline(input, translation))
	{
		if (!translation.empty())
		{
			wasChanged = true;
			dictionary.insert(make_pair(word, translation));
			output << "The word \"" << word << "\" has been saved in the dictionary as \"" << translation << "\".\n";
		}
	}
}

void TranslateWord(
	std::istream& input,
	std::ostream& output,
	std::map<std::string, std::string>& dictionary,
	std::string word,
	bool &wasChanged
)
{
	std::map<std::string, std::string>::iterator it;
	it = dictionary.find(word);
	if (it == dictionary.end())
	{
		AddNewWord(input, output, dictionary, word, wasChanged);
	}
	else
	{
		output << it->second << "\n";
	}
}

std::string Translate(std::map<std::string, std::string>& dictionary, std::map<std::string, std::string>::iterator it)
{
	return it->second;
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
			// std::map<std::string, std::string>::iterator it;
			auto it = dictionary.find(word);
			if (it == dictionary.end())
			{
				AddNewWord(input, output, dictionary, word, wasChanged);
			}
			else
			{
				std::string translation = Translate(dictionary, it);
				output << translation << "\n";
			}
		}
	}
}