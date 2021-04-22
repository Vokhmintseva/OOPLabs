#include "FunctionIdentifier.h"

FunctionIdentifier::FunctionIdentifier(std::string funName, std::string operand)
    :m_funName(funName),
    m_operand(operand)
{};

Countable::CountableType FunctionIdentifier::GetType() const
{
	return CountableType::FunctionIdentifier;
}

std::string FunctionIdentifier::GetName() const
{
    return m_funName;
}

std::string FunctionIdentifier::GetOperand() const
{
    return m_operand;
}


