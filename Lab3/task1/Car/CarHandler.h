#pragma once
#include <iostream>
#include <functional>
#include <map>
#include <string>
#include "Car.h"

class CarHandler
{
public:
	CarHandler(Car& car, std::istream& input, std::ostream& output);
	bool HandleCommand();
	static std::string GetDirection(Car::Direction dir);

private:
	bool Info(std::istream& args);
	bool EngineOn(std::istream& args);
	bool EngineOff(std::istream& args);
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);
	
private:
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;
	const ActionMap m_actionMap;
};