#include "FunctionExpression.h"
#include <regex>

FunctionExpression::FunctionExpression(const std::string& funName, const std::string& operand1, const std::string& operand2, const std::string& signStr)
	:m_funName(funName),
	m_operand1(operand1),
	m_operand2(operand2),
	m_sign(GetSign(signStr))
{};

FunctionExpression::Sign FunctionExpression::GetSign(std::string signStr)
{
	Sign s = Sign::Addition;
	for (auto sign : Signes)
	{
		if (sign.first == signStr)
		{
			s = sign.second;
		}
	}
	return s;
}

bool FunctionExpression::IsCorrectFunctionExpression(const std::string& expr)
{
	const std::regex r("^[a-zA-Z_]{1}[_0-9a-zA-Z]*[+\\-*\\/]{1}[a-zA-Z_]{1}[_0-9a-zA-Z]*$");
	return regex_match(expr, r);
}

Countable::CountableType FunctionExpression::GetType() const
{
	return CountableType::FunctionExpression;
}

std::string FunctionExpression::GetName() const
{
	return m_funName;
}

std::string FunctionExpression::GetOperand1() const
{
	return m_operand1;
}

std::string FunctionExpression::GetOperand2() const
{
	return m_operand2;
}

FunctionExpression::Sign FunctionExpression::GetSign() const
{
	return m_sign;
}