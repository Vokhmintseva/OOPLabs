// CBody.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "../BodiesLib/WorkSpace.h"

int main()
{
	WorkSpace workSpace(std::cin, std::cout);
	std::string command;
	while (!std::cin.eof() && !std::cin.fail())
	{
		if (!workSpace.HandleCommand() && !std::cin.eof())
		{
			std::cout << "Wrong command\n";
		}
	}
	workSpace.PrintBodiesInfo();
	workSpace.PrintMaxMassBody();
	workSpace.PrintBodyWithLeastWeightInWater();
	return 0;
}


