// HTTP_URL.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include "UrlHandler.h"

int main()
{
	UrlHandler urlHandler(std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		if (!urlHandler.HandleUrl())
		{
			std::cout << "Empty string" << std::endl;
		}
	}
	return 0;
}
