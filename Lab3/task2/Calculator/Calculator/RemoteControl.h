#pragma once
#include <functional>
#include <map>
#include <optional>

class Calculator;

class RemoteControl
{
public:
	RemoteControl(Calculator& calculator, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	struct Expression
	{
		std::string left;
		std::string right;
	};
	bool DeclareVariable(std::istream& args);
	bool SetVariableValue(std::istream& args);
	bool PrintCountable(std::istream& args);
	bool PrintVariables(std::istream& args);
	bool DeclareFunction(std::istream& args);
	bool PrintFunctions(std::istream& args);
private:
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	std::ostream& SetOutput(std::ostream& output);
	std::optional<RemoteControl::Expression> RetrievePartsOfExpression(const std::string& input);
	Calculator& m_calculator;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};
