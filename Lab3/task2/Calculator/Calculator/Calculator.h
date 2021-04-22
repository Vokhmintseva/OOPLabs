#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <optional>
#include <iostream>
#include "Variable.h"

class Calculator
{
public:
	Calculator();
	
	bool DeclareVariable(const std::string& name);
	bool DeclareFunction(std::string name, std::string expression);
	bool IsCountableDeclared(std::string name) const;
	
	bool SetVariableValue(std::string name, std::string newValue);
	std::optional<double> CountValue(const std::string& name) const;
	std::string GetErrorReason();
	std::map<std::string, double> GetAllVariables() const;
	std::map<std::string, double> GetAllFunctions() const;
	
private:
	double Calculate(const std::string& name, double& res) const;
	std::unique_ptr<Countable>& GetCountableRef(std::string name);
	std::optional<double> DetermineNewValueOfVariable(const std::string& newValue);
	std::vector<std::unique_ptr<Countable>> m_countables;
	std::string m_errorReason;
};

