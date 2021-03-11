#include <map>
#include <iostream>
#include <string>
#include "Decode.h"

using namespace std;

std::string HtmlDecode(std::string const& html)
{
	string decodedStr = html.substr(0);
	map<string, string> codes = { { "&quot;", "\"" },
		{ "&apos;", "`" },
		{ "&lt;", "<" },
		{ "&gt;", ">" },
		{ "&amp;", "&" } };

	map<string, string>::iterator it;
	size_t posApos = 0;
	size_t posSem = 0;
	posApos = decodedStr.find("&", posApos);
	while (posApos != string::npos)
	{
		posSem = decodedStr.find(";", posApos + 1);
		if (posSem == string::npos)
		{
			break;
		}
		string subStr = decodedStr.substr(posApos, posSem - posApos + 1);
		
		for (it = codes.begin(); it != codes.end(); it++)
		{
			if (subStr == it->first)
			{
				decodedStr.replace(posApos, posSem - posApos + 1, it->second);
				break;
			}
		}
		posApos = decodedStr.find("&", posApos + 1);
	}
	return decodedStr;
}

void DecodeLines(std::istream& input, std::ostream& output)
{
	string line;
	while (getline(input, line))
	{
		output << HtmlDecode(line);
		if (input.good())
		{
			output << "\n";
		}
	}
}