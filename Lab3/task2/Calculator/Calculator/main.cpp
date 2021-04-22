// Calculator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Calculator.h"
#include "RemoteControl.h"

int main()
{
	Calculator calculator;
	RemoteControl remoteControl(calculator, std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!remoteControl.HandleCommand())
		{
			std::cout << "Invalid command!" << std::endl;
		}
	}
	return 0;
}
