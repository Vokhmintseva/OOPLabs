#pragma once
#include <string>
#include "Countable.h"

class FunctionIdentifier :
    public Countable
{
public:
    FunctionIdentifier(std::string funName, std::string operand);
    CountableType GetType() const override;
    std::string GetName() const override;
    std::string GetOperand() const;
    ~FunctionIdentifier() = default;

private:
    std::string m_funName;
    std::string m_operand;
};
