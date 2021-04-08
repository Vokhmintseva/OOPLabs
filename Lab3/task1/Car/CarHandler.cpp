#include "CarHandler.h"

void CarHandler::Info(Car& car, std::ostream& output)
{
	std::string engineState = car.IsTurnedOn() ? "on.\n" : "off.\n";
	output << "The Engine is turned " << engineState;

	output << "Direction is " << car.GetDirection() << ".\n";

	output << "Speed is " << car.GetSpeed() << ".\n";

	output << "Gear is " << car.GetGear() << ".\n";
}

void CarHandler::EngineOn(Car& car, std::ostream& output)
{
	output << "Car's engine has been turned on.\n";
	car.TurnOnEngine();
}

bool CarHandler::EngineOff(Car& car, std::ostream& output)
{
	output << "Car's engine has been turned off.\n";
	return car.TurnOffEngine();
}

bool CarHandler::SetGear(Car& car, int newGear, std::ostream& output)
{
	bool wasGearSet = car.SetGear(newGear);
	if (wasGearSet)
	{
		output << "New gear has been switched on.\n";
		return true;
	}
	else
	{
		output << "New gear cannot be switched on. " << car.GetGearErrorReason() << ".\n";
		return false;
	}
}

bool CarHandler::SetSpeed(Car& car, int newSpeed, std::ostream& output)
{
	bool wasSpeedSet = car.SetSpeed(newSpeed);
	if (wasSpeedSet)
	{
		output << "Speed has been changed.\n";
		return true;
	}
	else
	{
		output << "Speed cannot be changed. " << car.GetSpeedErrorReason() << ".\n";
		return false;
	}
}