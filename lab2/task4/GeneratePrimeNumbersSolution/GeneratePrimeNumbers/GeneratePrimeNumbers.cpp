// GeneratePrimeNumbers.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <set>
#include "Generate.h"

using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		int upperBound = ParseArgs(argc, argv);
        set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
		PrintPrimeNumbers(cout, primeNumbers);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
		return 1;
	}
}
