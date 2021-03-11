// GeneratePrimeNumbers_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <set>
#include <sstream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../GeneratePrimeNumbers/Generate.h"
#include <stdio.h>

SCENARIO("prime numbers2")
{
	std::set<int> primeNumbers;
	WHEN("2 given")
	{
		primeNumbers = GeneratePrimeNumbersSet(2);
		REQUIRE(primeNumbers == std::set{2});
	}

	WHEN("0 given")
	{
		primeNumbers = GeneratePrimeNumbersSet(0);
		REQUIRE(primeNumbers.empty() == true);
	}
	
	WHEN("negative number given")
	{
		primeNumbers = GeneratePrimeNumbersSet(-5);
		REQUIRE(primeNumbers.empty() == true);
	}
	
	WHEN("all prime numbers below 19")
	{
		primeNumbers = GeneratePrimeNumbersSet(19);
		REQUIRE(primeNumbers == std::set{ 2, 3, 5, 7, 11, 13, 17, 19 });
	}
	
	#ifdef NDEBUG
	WHEN("all prime numbers below 100 000 000 count")
	{
		primeNumbers = GeneratePrimeNumbersSet(100000000);
		std::set<int>::iterator it;
		int num = 0;
		for (it = primeNumbers.begin(); it != primeNumbers.end(); ++it)
		{
			num++;
		}
		REQUIRE(num == 5761455);
	}	
	#endif
}

