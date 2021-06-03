#pragma once
#include <istream>

class UrlHandler
{
public:
	UrlHandler(std::istream& input, std::ostream& output);
	bool HandleUrl();
private:
	std::istream& m_input;
	std::ostream& m_output;
};
