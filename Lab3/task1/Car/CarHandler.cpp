#include <iostream>
#include <sstream>
#include <string>
//#include <regex>
#include "CarHandler.h"
#include "Car.h"

using namespace std::placeholders;

CarHandler::CarHandler(Car& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "Info", bind(&CarHandler::Info, this, _1) },
		  { "EngineOn", bind(&CarHandler::EngineOn, this, _1) },
		  { "EngineOff", bind(&CarHandler::EngineOff, this, _1) },
		  { "SetGear", bind(&CarHandler::SetGear, this, _1) },
		  { "SetSpeed", bind(&CarHandler::SetSpeed, this, _1) },
	  })
{
}

bool CarHandler::HandleCommand()
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

const std::string CarHandler::GetDirection(Car::Direction dir)
{
	std::string direction;
	if (dir == Car::Direction::Static)
	{
		direction = "static";
	}
	if (dir == Car::Direction::Forward)
	{
		direction = "forward";
	}
	if (dir == Car::Direction::Backward)
	{
		direction = "backward";
	}
	return std::move(direction);
}

bool CarHandler::Info(std::istream& args)
{
	std::string engineState = m_car.IsTurnedOn() ? "on.\n" : "off.\n";
	m_output << "The Engine is turned " << engineState;
	Car::Direction dir = m_car.GetDirection();
	std::string direction = GetDirection(dir);

	m_output << "Direction is " << direction << ".\n";

	m_output << "Speed is " << m_car.GetSpeed() << ".\n";

	m_output << "Gear is " << m_car.GetGear() << ".\n";
	return true;
}

bool CarHandler::EngineOn(std::istream& args)
{
	m_output << "Car's engine has been turned on.\n";
	m_car.TurnOnEngine();
	return true;
}

bool CarHandler::EngineOff(std::istream& args)
{
	if (!m_car.TurnOffEngine())
	{
		m_output << m_car.GetErrorReason() << "\n";
	}
	m_output << "Car's engine has been turned off.\n";
	return true;
}

bool CarHandler::SetGear(std::istream& args)
{
	int newGear;
	if (args >> newGear)
	{
		if (args.eof())
		{
			if (m_car.SetGear(newGear))
			{
				m_output << "New gear has been switched on.\n";
				return true;
			}
			else
			{
				m_output << "New gear cannot be switched on. " << m_car.GetErrorReason() << ".\n";
				return true;
			}
		}
	}
	return false;
}

bool CarHandler::SetSpeed(std::istream& args)
{
	int newSpeed;
	if (args >> newSpeed)
	{
		if (args.eof())
		{
			if (m_car.SetSpeed(newSpeed))
			{
				m_output << "Speed has been changed.\n";
				return true;
			}
			else
			{
				m_output << "Speed cannot be changed. " << m_car.GetErrorReason() << ".\n";
				return true;
			}
		}
	}
	return false;
}
