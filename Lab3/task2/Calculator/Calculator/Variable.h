#pragma once
#include <string>
#include <regex>
#include "Countable.h"

class Variable :
	public Countable
{
public:
	Variable(std::string name);
	Variable(std::string name, double value);
	~Variable() = default;
	
	CountableType Countable::GetType() const override;
	std::string GetName() const override;
	double GetValue() const;
	void SetValue(double value);

private:
	std::string m_name;
	std::string m_type;
	double m_value;
};
