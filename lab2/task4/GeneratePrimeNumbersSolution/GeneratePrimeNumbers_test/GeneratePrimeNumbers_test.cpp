// GeneratePrimeNumbers_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
#include <set>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../GeneratePrimeNumbers/Generate.h"

SCENARIO("prime numbers below 100")
{
	std::set<int> primeNumbers = GeneratePrimeNumbersSet(100);
	std::ostringstream output;
	PrintPrimeNumbers(output, primeNumbers);
	REQUIRE(output.str() == "2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 ");
}



	



