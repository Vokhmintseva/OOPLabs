#include "Car.h"
#include "CarHandler.h"
#include <iostream>

int main()
{
	Car car;
	CarHandler carHandler (car, std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!carHandler.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
	return 0;
}
