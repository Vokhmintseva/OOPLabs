#define CATCH_CONFIG_MAIN
#include <iostream>
#include <vector>
#include "../FindMaxEx/FindMaxEx.h"
#include "../../../../catch.hpp"

TEST_CASE("empty vector")
{
	std::vector<float> floatVector;
	float test;
	CHECK((FindMax<float>(floatVector, test, Less<float>())) == false);
}

TEST_CASE("int vector")
{
	std::vector<int> intVector = {25, 49, 87, 64, 87, 29, -5};
	int test;
	CHECK((FindMax<int>(intVector, test, Less<int>())) == true);
	CHECK(test == 87);
}

TEST_CASE("std::string vector")
{
	std::vector<std::string> stringVector = { "cat", "cats", "april", "average", "brick" };
	std::string test;
	CHECK((FindMax<std::string>(stringVector, test, Less<std::string>())) == true);
	CHECK(test == "cats");
}

TEST_CASE("const char* vector")
{
	std::vector<const char*> stringVector = { "day", "copy", "copies", "lasts", "last" };
	const char* test;
	CHECK((FindMax<const char*>(stringVector, test, Less<const char*>())) == true);
	CHECK(test == "lasts");
}

TEST_CASE("sportsman vector")
{
	std::vector<Sportsman> sportsmenVector =
	{
		{"some sportsman1", 28, 80},
		{"some sportsman2", 35, 96},
		{"some sportsman3", 45, 95},
		{"some sportsman4", 39, 96},
		{"some sportsman5", 45, 95}
	};
	
	Sportsman test;

	CHECK(FindMax<Sportsman>(sportsmenVector, test, CompareSportsmenWeight()) == true);
	CHECK(test.fullName == "some sportsman2");

	CHECK(FindMax<Sportsman>(sportsmenVector, test, CompareSportsmenAge()) == true);
	CHECK(test.fullName == "some sportsman3");
}

TEST_CASE("emppty sportsman vector")
{
	std::vector<Sportsman> sportsmenVector;
	Sportsman test;
	CHECK(FindMax<Sportsman>(sportsmenVector, test, CompareSportsmenWeight()) == false);
	CHECK(FindMax<Sportsman>(sportsmenVector, test, CompareSportsmenAge()) == false);
}

TEST_CASE("1 sportsman in vector")
{
	std::vector<Sportsman> sportsmenVector =
	{
		{"single", 28, 80}
	};

	Sportsman test;

	CHECK(FindMax<Sportsman>(sportsmenVector, test, CompareSportsmenWeight()) == true);
	CHECK(test.fullName == "single");

	CHECK(FindMax<Sportsman>(sportsmenVector, test, CompareSportsmenAge()) == true);
	CHECK(test.fullName == "single");
}
