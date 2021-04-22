#include "Calculator.h"
#include <math.h>
#include <regex>
#include "FunctionIdentifier.h"
#include "FunctionExpression.h"
#include "Variable.h"

Calculator::Calculator() {};

bool Calculator::DeclareVariable(const std::string& name)
{
	if (IsCountableDeclared(name))
	{
		m_errorReason = "Already declared";
		return false;
	}
	if (!Countable::isCorrectIdentifierName(name))
	{
		m_errorReason = "Incorrect name";
		return false;
	}
	m_countables.emplace_back(std::make_unique<Variable>(name));
	m_errorReason = "";
	return true;
}

std::unique_ptr<Countable>& Calculator::GetCountableRef(std::string name)
{
	for (auto& var : m_countables)
	{
		if (var->GetName() == name)
		{
			return var;
		}
	}
	static std::unique_ptr<Countable> notFound(nullptr);
	return notFound;
}

std::optional<double> Calculator::DetermineNewValueOfVariable(const std::string& newValue)
{
	double value = 0;
	const std::regex r("^-{0,1}\\d+(\\.\\d+){0,1}$");
	if (regex_match(newValue, r)) //это число
	{
		value = stod(newValue);
	}
	else if (!Countable::isCorrectIdentifierName(newValue)) //это идентификатор с некорректным именем
	{
		return std::nullopt;
	}
	else //это идентификатор с корректным именем
	{
		std::unique_ptr<Countable>& countableRef = GetCountableRef(newValue);

		if (countableRef == nullptr) //такого идентификатора не существует
		{
			return std::nullopt;
		}
		else // этот идентификатор существует
		{
			std::string name = countableRef->GetName();
			auto val = CountValue(name);
			value = val.value();
		}
	}
	return value;
}

bool Calculator::SetVariableValue(std::string name, std::string newValue)
{
	if (!Countable::isCorrectIdentifierName(name))
	{
		m_errorReason = "Incorrect variable name given on the left side";
		return false;
	}
	auto value = DetermineNewValueOfVariable(newValue);
	if (!value)
	{
		m_errorReason = "Incorrect value on the right side";
		return false;
	}
	
	std::unique_ptr<Countable>& countableRef = GetCountableRef(name);
	if (countableRef == nullptr)
	{
		m_countables.emplace_back(std::make_unique<Variable>(name, value.value()));
	}
	else
	{
		if (countableRef->GetType() == Countable::CountableType::Variable)
		{
			Variable& variable = static_cast<Variable&>(*countableRef);
			variable.SetValue(value.value());
		}
		else
		{
			m_errorReason = "not variable name given on the left side";
			return false;
		}
	}
	m_errorReason = "";
	return true;
}

bool Calculator::IsCountableDeclared(std::string name) const
{
	for (auto& var : m_countables)
	{
		if (var->GetName() == name)
		{
			return true;
		}
	}
	return false;
}

std::string Calculator::GetErrorReason()
{
	return m_errorReason;
}

std::optional<double> Calculator::CountValue(const std::string& name) const
{
	if (IsCountableDeclared(name))
	{
		double res = 0;
		return Calculate(name, res);
	}
	else
	{
		return std::nullopt;
	}
}

double Calculator::Calculate(const std::string& name, double &res) const
{
	if (res == std::numeric_limits<double>::quiet_NaN())
	{
		return std::numeric_limits<double>::quiet_NaN();
	}
	
	for (auto& var : m_countables)
	{
		if (var->GetName() == name && var->GetType() == Countable::CountableType::FunctionExpression)
		{
			FunctionExpression& expr = static_cast<FunctionExpression&>(*var);
			FunctionExpression::Sign sign = expr.GetSign();
			double res1 = 0;
			res1 = Calculate(expr.GetOperand1(), res1);
			double res2 = 0;
			res2 = Calculate(expr.GetOperand2(), res2);
			if (sign == FunctionExpression::Sign::Addition)
			{
				res = res1 + res2;
			}
			if (sign == FunctionExpression::Sign::Subtraction)
			{
				res = res1 - res2;
			}
			if (sign == FunctionExpression::Sign::Multiplication)
			{
				res = res1 * res2;
			}
			if (sign == FunctionExpression::Sign::Division)
			{
				res = res1 / res2;
			}
			break;
		}
		if (var->GetName() == name && var->GetType() == Countable::CountableType::FunctionIdentifier)
		{
			FunctionIdentifier& funIdentifier = static_cast<FunctionIdentifier&>(*var);
			res = Calculate(funIdentifier.GetOperand(), res);
			break;
		}
		if (var->GetName() == name && var->GetType() == Countable::CountableType::Variable)
		{
			Variable& variable = static_cast<Variable&>(*var);
			res = variable.GetValue();
			break;
		}
	}
	return res;
}

std::map<std::string, double> Calculator::GetAllVariables() const
{
	std::map <std::string, double> vars;
	for (auto& var : m_countables)
	{
		if (var->GetType() == Countable::CountableType::Variable)
		{
			vars[var->GetName()] = static_cast<Variable&>(*var).GetValue();
		}
	}
	return vars;
}

std::map<std::string, double> Calculator::GetAllFunctions() const
{
	std::map <std::string, double> functions;
	for (auto& var : m_countables)
	{
		if (var->GetType() == Countable::CountableType::FunctionExpression ||
			var->GetType() == Countable::CountableType::FunctionIdentifier)
		{
			std::string functionName = var->GetName();
			double res = 0;
			functions[var->GetName()] = Calculate(functionName, res);
		}
	}
	return functions;
}

bool Calculator::DeclareFunction(std::string name, std::string expression)
{

	if (IsCountableDeclared(name))
	{
		m_errorReason = "Already declared";
		return false;
	}

	if (!Countable::isCorrectIdentifierName(name))
	{
		m_errorReason = "Incorrect function name given";
		return false;
	}

	if (Countable::isCorrectIdentifierName(expression)) //если fn <идентификатор1> = <идентификатор2>
	{
		if (!IsCountableDeclared(expression))
		{
			m_errorReason = "No such identifier declared earlier";
			return false;
		}
		m_countables.emplace_back(std::make_unique<FunctionIdentifier>(name, expression));
		m_errorReason = "";
		return true;
	}
	
	if (FunctionExpression::IsCorrectFunctionExpression(expression)) //fn <идентификатор1> = <идентификатор2>[<операция> <идентификатор3>
	{
		
		const std::regex re("[+\\-*\\/]");
		std::smatch match;
		if (std::regex_search(expression, match, re))
		{
			const std::string sign = match[0];
			
			size_t signPos = expression.find(sign);
			if (signPos != std::string::npos)
			{
				std::string operand1, operand2;
				unsigned int exprLen = expression.length();
				operand1.append(expression, 0, signPos);
				operand2.append(expression, signPos + 1, exprLen - signPos - 1);
				if (
					Countable::isCorrectIdentifierName(operand1) &&
					Countable::isCorrectIdentifierName(operand2) &&
					IsCountableDeclared(operand1) &&
					IsCountableDeclared(operand2)
					)
				{
					m_countables.emplace_back(std::make_unique<FunctionExpression>(name, operand1, operand2, sign));
					m_errorReason = "";
					return true;
				}
			}
		}
	}
	m_errorReason = "Incorrect value on the right side";
	return false;
}
