#pragma once
#include <string>
class Countable
{
public:
	
	enum class CountableType
	{
		FunctionIdentifier,
		FunctionExpression,
		Variable
	};
	
	virtual CountableType GetType() const = 0;
	virtual std::string GetName() const = 0;

	static bool isCorrectIdentifierName(const std::string& identifierName);

	virtual ~Countable() = default;

};

