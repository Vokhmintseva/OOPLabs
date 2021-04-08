#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Car.h"
#include "CarHandler.h"

int main()
{
	Car car;
	
	std::string input;
	while (std::getline(std::cin, input))
	{
		std::istringstream strm(input);
		std::string command;
		int param;
	    strm >> command;
		
		if (command == "Info")
		{
			CarHandler::Info(car, std::cout);
			continue;
		}

		if (command == "EngineOn")
		{
			CarHandler::EngineOn(car, std::cout);
			continue;
		}

		if (command == "EngineOff")
		{
			CarHandler::EngineOff(car, std::cout);
			continue;
		}

		if (command == "SetGear")
		{
			if (strm >> param)
			{
				if (strm.eof())
				{
					CarHandler::SetGear(car, param, std::cout);
					continue;
				}
			}
		}

		if (command == "SetSpeed")
		{
			if (strm >> param)
			{
				if (strm.eof())
				{
					CarHandler::SetSpeed(car, param, std::cout);
					continue;
				}
			}
		}
		
		std::cout << "Invalid command\n";
	}
	return 0;
}