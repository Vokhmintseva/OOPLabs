#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include <math.h>
#include "RemoteControl.h"
#include "Calculator.h"

using namespace std::placeholders;

RemoteControl::RemoteControl(Calculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(SetOutput(output))
	, m_actionMap({
		  { "var", bind(&RemoteControl::DeclareVariable, this, _1) },
		  { "let", bind(&RemoteControl::SetVariableValue, this, _1) },
		  { "print", bind(&RemoteControl::PrintCountable, this, _1) },
		  { "printvars", bind(&RemoteControl::PrintVariables, this, _1) },
		  { "fn", bind(&RemoteControl::DeclareFunction, this, _1)},
		  { "printfns", bind(&RemoteControl::PrintFunctions, this, _1)}
		})
{
}

std::ostream& RemoteControl::SetOutput(std::ostream& output)
{
	output.setf(std::ios::fixed);
	output.precision(2);
	return output;
}

bool RemoteControl::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}
	return false;
}

bool RemoteControl::DeclareVariable(std::istream& args)
{
	std::string input;
	if (args >> input)
	{
		if (m_calculator.DeclareVariable(input))
		{
			return true;
		}
		else
		{
			m_output << m_calculator.GetErrorReason() << "\n";
		}
	}
	return false;
}

bool RemoteControl::SetVariableValue(std::istream& args)
{
	std::string input;
	if (args >> input)
	{
		auto expr = RetrievePartsOfExpression(input);
		if (expr)
		{
			std::string varName = expr->left;
			std::string varValue = expr->right;
			if (m_calculator.SetVariableValue(varName, varValue))
			{
				return true;
			}
			else
			{
				m_output << m_calculator.GetErrorReason() << "\n";
			}
		}
	}
	return false;
}

bool RemoteControl::PrintCountable(std::istream& args)
{
	std::string varName;
	args >> varName;
	auto varValue = m_calculator.CountValue(varName);
	if (varValue)
	{
		m_output << varValue.value() << "\n";
		return true;
	}
	else
	{
		m_output << "Not declared\n";
		return false;
	}
}

bool RemoteControl::PrintVariables(std::istream& args)
{
	std::map<std::string, double> vars = m_calculator.GetAllVariables();
	for (auto var : vars)
	{
		m_output << var.first << ":" << var.second << "\n";
	}
	return true;
}

std::optional<RemoteControl::Expression> RemoteControl::RetrievePartsOfExpression(const std::string& input)
{
	size_t eqvPos = input.find('=');
	if (eqvPos != std::string::npos)
	{
		std::string leftPart, rightPart;
		unsigned int inputLen = input.length();
		leftPart.append(input, 0, eqvPos);
		rightPart.append(input, eqvPos + 1, inputLen - eqvPos - 1);
		if (!leftPart.empty() && !rightPart.empty())
		{
			Expression expr;
			expr.left = leftPart;
			expr.right = rightPart;
			return expr;
		}
	}
	m_output << "Incorrect expression\n";
	return std::nullopt;
}

bool RemoteControl::DeclareFunction(std::istream& args)
{
	std::string input;
	if (args >> input)
	{
		auto expr = RetrievePartsOfExpression(input);
		if (expr)
		{
			std::string funName = expr->left;
			std::string rightPart = expr->right;
			if (m_calculator.DeclareFunction(funName, rightPart))
			{
				return true;
			}
			else
			{
				m_output << m_calculator.GetErrorReason() << "\n";
			}
		}
	}
	return false;
}

bool RemoteControl::PrintFunctions(std::istream& args)
{
	std::map<std::string, double> vars = m_calculator.GetAllFunctions();
	for (auto var : vars)
	{
		m_output << var.first << ":" << var.second << "\n";
	}
	return true;
}