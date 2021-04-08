#pragma once
#include <iostream>
#include <sstream>
#include "Car.h"

class CarHandler
{

public:
	//CarHandler();
	static void Info(Car& car, std::ostream& output);
	static void EngineOn(Car& car, std::ostream& output);
	static bool EngineOff(Car& car, std::ostream& output);
	static bool SetGear(Car& car, int newGear, std::ostream& output);
	static bool SetSpeed(Car& car, int newSpeed, std::ostream& output);
};
