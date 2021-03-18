// VectorTask_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
#include <vector>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../VectorTask/HandleVector.h"

SCENARIO("empty string")
{
	std::istringstream inputStrm("");
	std::vector<double> arr = getVector(inputStrm);
	std::ostringstream outputStrm;
	printVector(outputStrm, arr);
	REQUIRE(outputStrm.str() == "");
	outputStrm.str("");
	multiplyElements(arr);
	printVector(outputStrm, arr);
	REQUIRE(outputStrm.str() == "");
	outputStrm.str("");
	std::sort(arr.begin(), arr.end());
	printVector(outputStrm, arr);
	REQUIRE(outputStrm.str() == "");
}

SCENARIO("any string")
{
	std::istringstream inputStrm("8 7.3 7.0 4.00001 9.0 3.0 8.0002 27.0");
	std::vector<double> arr = getVector(inputStrm);
	std::ostringstream outputStrm;
	
	SECTION("print")
	{
		printVector(outputStrm, arr);
		REQUIRE(outputStrm.str() == "8.000 7.300 7.000 4.000 9.000 3.000 8.000 27.000 ");
	}

	SECTION("multiply and print")
	{
		multiplyElements(arr);
		printVector(outputStrm, arr);
		REQUIRE(outputStrm.str() == "8.000 7.300 7.000 4.000 72.000 24.000 8.000 216.000 ");
	}

	SECTION("sort and print")
	{
		std::sort(arr.begin(), arr.end());
		printVector(outputStrm, arr);
		REQUIRE(outputStrm.str() == "3.000 4.000 7.000 7.300 8.000 8.000 9.000 27.000 ");
	}

	SECTION("multiply, sort and print")
	{
		multiplyElements(arr);
		std::sort(arr.begin(), arr.end());
		printVector(outputStrm, arr);
		REQUIRE(outputStrm.str() == "4.000 7.000 7.300 8.000 8.000 24.000 72.000 216.000 ");
	}
}

SCENARIO("any string-2")
{
	std::istringstream inputStrm("8.00001 4 -3 0 -2 -27 3.00001");
	std::vector<double> arr = getVector(inputStrm);
	std::ostringstream outputStrm;

	SECTION("print")
	{
		printVector(outputStrm, arr);
		REQUIRE(outputStrm.str() == "8.000 4.000 -3.000 0.000 -2.000 -27.000 3.000 ");
	}
	
	SECTION("multiply, sort and print")
	{
		multiplyElements(arr);
		std::sort(arr.begin(), arr.end());
		printVector(outputStrm, arr);
		REQUIRE(outputStrm.str() == "-18.000 -2.000 -2.000 0.000 3.000 4.000 8.000 ");
	}
}

SCENARIO("any string-3")
{
	std::istringstream inputStrm("10.0000000001 4.25 0 0 0 -15 0 0 -3.00000001 4.0 21 -9 2");
	std::vector<double> arr = getVector(inputStrm);
	std::ostringstream outputStrm;
	multiplyElements(arr);
	std::sort(arr.begin(), arr.end());
	printVector(outputStrm, arr);
	REQUIRE(outputStrm.str() == "-12.857 -7.714 -3.000 0.000 0.000 0.000 0.000 0.000 2.000 4.000 4.250 10.000 18.000 ");
}
