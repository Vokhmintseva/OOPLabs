#include <map>
#include <iostream>
#include <string>
#include "Decode.h"

using namespace std;

unsigned int GetMaxLenOfSearchStr(const map<string, string> &codes)
{
	unsigned int maxLenOfSearchStr = 0;
	for (const auto& code : codes)
	{
		if (code.first.length() > maxLenOfSearchStr)
		{
			maxLenOfSearchStr = code.first.length();
		}
	}
	return maxLenOfSearchStr;
}

std::string HtmlDecode(std::string const& html)
{
	const map<string, string> codes =
	{
		{ "&quot;", "\"" },
		{ "&apos;", "'" },
		{ "&lt;", "<" },
		{ "&gt;", ">" },
		{ "&amp;", "&" }
	};

	unsigned int maxLenOfSearchStr = GetMaxLenOfSearchStr(codes);

	string decodedStr = "";
	size_t prevPos = 0;
	size_t newPos = html.find('&', prevPos);
	while (newPos != std::string::npos)
	{
		decodedStr.append(html, prevPos, newPos - prevPos);
		string captureStr = "";
		captureStr.append(html, newPos, maxLenOfSearchStr);
		bool found = false;
		unsigned int offset = 1;
		for (const auto& [key, value] : codes)
		{
			string possibleStr = "";
			possibleStr.append(captureStr, 0, key.length());
			if (key == possibleStr)
			{
				decodedStr.append(value);
				offset = key.length();
				found = true;
				break;
			}
		}
		if (!found)
		{
			decodedStr.append("&");
		}
		prevPos = newPos + offset;
		newPos = html.find('&', prevPos);
	}
	decodedStr.append(html, prevPos);
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