#pragma once
#include <string>
#include <map>
#include "Countable.h"

class FunctionExpression :
    public Countable
{
public:
    enum class Sign
    {
        Addition,
        Subtraction,
        Multiplication,
        Division
    };
    
    FunctionExpression(const std::string& funName, const std::string& operand1, const std::string& operand2, const std::string& signStr);
    CountableType GetType() const override;
    std::string GetName() const override;
    std::string GetOperand1() const;
    std::string GetOperand2() const;
    Sign GetSign() const;
    static bool IsCorrectFunctionExpression(const std::string& expr);
    ~FunctionExpression() = default;

private:
    const std::map<std::string, Sign> Signes =
    {
        {"+", Sign::Addition},
        {"-", Sign::Subtraction},
        {"*", Sign::Multiplication},
        {"/", Sign::Division}
    };
    Sign GetSign(std::string signStr);

    std::string m_funName;
    std::string m_operand1;
    std::string m_operand2;
    Sign m_sign;
};

