#include "Countable.h"
#include <regex>

/*Countable::Countable(std::string name)
	:m_name(name)
{};*/

bool Countable::isCorrectIdentifierName(const std::string& identifierName)
{
	const std::regex r("^[a-zA-Z_]{1}[_0-9a-zA-Z]*$");
	return regex_match(identifierName, r);
}