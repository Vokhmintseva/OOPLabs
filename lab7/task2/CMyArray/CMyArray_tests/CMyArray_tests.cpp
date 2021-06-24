#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../CMyArray/MyArray.h"
#include "../../../../catch.hpp"

/*TEST_CASE("empty vector of float")
{
	MyArray<float> floatVector;
	CHECK(floatVector.GetSize() == 0);
	REQUIRE_THROWS_WITH(floatVector[0], "index is out of range");
}

TEST_CASE("empty vector of strings")
{
	MyArray<std::string> stringVector;
	CHECK(stringVector.GetSize() == 0);
	REQUIRE_THROWS_WITH(stringVector[0], "index is out of range");
}

TEST_CASE("creating vector of strings with initialized list")
{
	MyArray<std::string> stringVector{"1", "2", "3", "4"};
	CHECK(stringVector.GetSize() == 4);
	CHECK(stringVector[0] == "1");
	CHECK(stringVector[1] == "2");
	CHECK(stringVector[2] == "3");
	CHECK(stringVector[3] == "4");
}

TEST_CASE("copy construtor")
{
	MyArray<std::string> stringVector{ "1", "2", "3", "4" };
	MyArray<std::string> newVector(stringVector);
	CHECK(stringVector.GetSize() == 4);
	CHECK(newVector[0] == "1");
	CHECK(newVector[1] == "2");
	CHECK(newVector[2] == "3");
	CHECK(newVector[3] == "4");

	CHECK(stringVector.GetSize() == 4);
	CHECK(stringVector[0] == "1");
	CHECK(stringVector[1] == "2");
	CHECK(stringVector[2] == "3");
	CHECK(stringVector[3] == "4");
}

TEST_CASE("copy constructor of empty vector")
{
	MyArray<float> floatVector;
	MyArray<float> newVector(floatVector);
	CHECK(newVector.GetSize() == 0);
	REQUIRE_THROWS_WITH(newVector[0], "index is out of range");
}

TEST_CASE("move constructor of empty vector")
{
	MyArray<float> floatVector;
	MyArray<float> newVector(std::move(floatVector));
	CHECK(newVector.GetSize() == 0);
	REQUIRE_THROWS_WITH(newVector[0], "index is out of range");
}

TEST_CASE("move construtor")
{
	MyArray<std::string> stringVector{ "1", "2", "3", "4" };
	MyArray<std::string> newVector(std::move(stringVector));
	CHECK(stringVector.GetSize() == 4);
	CHECK(newVector[0] == "1");
	CHECK(newVector[1] == "2");
	CHECK(newVector[2] == "3");
	CHECK(newVector[3] == "4");
}

TEST_CASE("operator= for l-value")
{
	MyArray<std::string> v1{ "1", "2", "3", "4" };
	MyArray<std::string> v2{ "1", "2" };
	v2 = v1;
	CHECK(v2.GetSize() == 4);
	CHECK(v2[0] == "1");
	CHECK(v2[1] == "2");
	CHECK(v2[2] == "3");
	CHECK(v2[3] == "4");

	CHECK(v1.GetSize() == 4);
	CHECK(v1[0] == "1");
	CHECK(v1[1] == "2");
	CHECK(v1[2] == "3");
	CHECK(v1[3] == "4");
}

TEST_CASE("resize method")
{
	MyArray<std::string> v{ "1", "2", "3", "4" };
	
	SECTION("increase size") {
		v.Resize(6);
		CHECK(v.GetSize() == 6);
		CHECK(v[0] == "1");
		CHECK(v[1] == "2");
		CHECK(v[2] == "3");
		CHECK(v[3] == "4");
		CHECK(v[4] == "");
		CHECK(v[5] == "");
		REQUIRE_THROWS_WITH(v[6], "index is out of range");
	}

	SECTION("decrease size") {
		v.Resize(2);
		CHECK(v.GetSize() == 2);
		CHECK(v[0] == "1");
		CHECK(v[1] == "2");
		REQUIRE_THROWS_WITH(v[2], "index is out of range");
	}

	SECTION("decrease size up to 0") {
		v.Resize(0);
		CHECK(v.GetSize() == 0);
		REQUIRE_THROWS_WITH(v[0], "index is out of range");
	}

	SECTION("change to the same size") {
		v.Resize(4);
		CHECK(v.GetSize() == 4);
		CHECK(v[0] == "1");
		CHECK(v[1] == "2");
		CHECK(v[2] == "3");
		CHECK(v[3] == "4");
		REQUIRE_THROWS_WITH(v[4], "index is out of range");
	}
	
	SECTION("increase size for float") {
		MyArray<float> v{ 15.145f, -3.27f, -0.01f, 158.321f };
		v.Resize(10);
		CHECK(v.GetSize() == 10);
		CHECK(v[0] == 15.145f);
		CHECK(v[1] == -3.27f);
		CHECK(v[2] == -0.01f);
		CHECK(v[3] == 158.321f);
		CHECK(v[4] == 0);
		CHECK(v[5] == 0);
		CHECK(v[6] == 0);
		CHECK(v[7] == 0);
		CHECK(v[8] == 0);
		CHECK(v[9] == 0);
		REQUIRE_THROWS_WITH(v[10], "index is out of range");
	}
}

TEST_CASE("operator= for r-value")
{
	MyArray<std::string> v = {"1", "2", "3", "4", "5", "6"};
	v = MyArray<std::string>({ "1", "2", "3", "4" });
	CHECK(v.GetSize() == 4);
	CHECK(v[0] == "1");
	CHECK(v[1] == "2");
	CHECK(v[2] == "3");
	CHECK(v[3] == "4");
}

TEST_CASE("not empty vector of float") {
	MyArray<float> floatVector;
	std::ostringstream output;
	
	WHEN("push elements and check size") {
		floatVector.PushBack(1.5f);
		CHECK(floatVector.GetSize() == 1);
		floatVector.PushBack(2.5f);
		CHECK(floatVector.GetSize() == 2);
		floatVector.PushBack(3.5f);
		CHECK(floatVector.GetSize() == 3);
		floatVector.PushBack(4.5f);
		CHECK(floatVector.GetSize() == 4);
		floatVector.PushBack(5.5f);
		CHECK(floatVector.GetSize() == 5);
		floatVector.PushBack(6.5f);
		CHECK(floatVector.GetSize() == 6);
		floatVector.PushBack(7.5f);
		CHECK(floatVector.GetSize() == 7);
		floatVector.PushBack(8.5f);
		CHECK(floatVector.GetSize() == 8);
		floatVector.PushBack(9.5f);
		CHECK(floatVector.GetSize() == 9);
		floatVector.PushBack(10.5f);
		CHECK(floatVector.GetSize() == 10);
		floatVector.PushBack(11.5f);
		CHECK(floatVector.GetSize() == 11);
		floatVector.PushBack(12.5f);
		CHECK(floatVector.GetSize() == 12);

		THEN("range based for loop") {
			for (auto& item : floatVector)
			{
				output << item << '\n';
			}
			CHECK(output.str() == "1.5\n2.5\n3.5\n4.5\n5.5\n6.5\n7.5\n8.5\n9.5\n10.5\n11.5\n12.5\n");
		}

		AND_THEN("access by index") {
			CHECK(floatVector[0] == 1.5);
			CHECK(floatVector[1] == 2.5);
			CHECK(floatVector[2] == 3.5);
			CHECK(floatVector[3] == 4.5);
			CHECK(floatVector[4] == 5.5);
			CHECK(floatVector[5] == 6.5);
			CHECK(floatVector[6] == 7.5);
			CHECK(floatVector[7] == 8.5);
			CHECK(floatVector[8] == 9.5);
			CHECK(floatVector[9] == 10.5);
			CHECK(floatVector[10] == 11.5);
			CHECK(floatVector[11] == 12.5);
			REQUIRE_THROWS_WITH(floatVector[12], "index is out of range");
		}
	}
}

TEST_CASE("not empty vector of strings") {
	MyArray<std::string> stringVector;
	std::ostringstream output;

	WHEN("push elements and check size") {
		stringVector.PushBack("1");
		CHECK(stringVector.GetSize() == 1);
		stringVector.PushBack("2");
		CHECK(stringVector.GetSize() == 2);
		stringVector.PushBack("3");
		CHECK(stringVector.GetSize() == 3);
		stringVector.PushBack("4");
		CHECK(stringVector.GetSize() == 4);
		stringVector.PushBack("5");
		CHECK(stringVector.GetSize() == 5);
		stringVector.PushBack("6");
		CHECK(stringVector.GetSize() == 6);

		THEN("range based for loop") {
			for (auto& item : stringVector)
			{
				output << item;
			}
			CHECK(output.str() == "123456");
		}

		AND_THEN("access by index") {
			CHECK(stringVector[0] == "1");
			CHECK(stringVector[1] == "2");
			CHECK(stringVector[2] == "3");
			CHECK(stringVector[3] == "4");
			CHECK(stringVector[4] == "5");
			CHECK(stringVector[5] == "6");
			REQUIRE_THROWS_WITH(stringVector[6], "index is out of range");
		}
		AND_WHEN("change elements accessed by index") {
			stringVector[0] = "new string 1";
			stringVector[1] = "new string 2";
			stringVector[2] = "new string 3";

			THEN("values have been changed") {
				CHECK(stringVector[0] == "new string 1");
				CHECK(stringVector[1] == "new string 2");
				CHECK(stringVector[2] == "new string 3");
				CHECK(stringVector[3] == "4");
				CHECK(stringVector[4] == "5");
				CHECK(stringVector[5] == "6");
			}
		}
	}
}

TEST_CASE("forward string iterator")
{
	MyArray<std::string> stringVector{ "1", "2", "3", "4", "5" };
	SECTION("increment postfix  iterator until the end") {
		auto it = stringVector.begin();
		CHECK(*it++ == "1");
		CHECK(*it++ == "2");
		CHECK(*it++ == "3");
		CHECK(*it++ == "4");
		CHECK(*it++ == "5");
		CHECK(it-- == stringVector.end());
		CHECK(it != stringVector.begin());
		CHECK(*it == "5");
	}

	SECTION("increment prefix iterator until the end") {
		auto it = stringVector.begin();
		CHECK(*it == "1");
		CHECK(*++it == "2");
		CHECK(*++it == "3");
		CHECK(*++it == "4");
		CHECK(*++it == "5");
		CHECK(++it == stringVector.end());
		CHECK(it != stringVector.begin());
	}

	SECTION("decrement postfix iterator until begin") {
		auto it = stringVector.end();
		it--;
		CHECK(*it-- == "5");
		CHECK(*it-- == "4");
		CHECK(*it-- == "3");
		CHECK(*it-- == "2");
		CHECK(*it == "1");
		CHECK(it == stringVector.begin());
		CHECK(it != stringVector.end());
	}

	SECTION("decrement prefix iterator until begin") {
		auto it = stringVector.end();
		CHECK(*--it == "5");
		CHECK(*--it == "4");
		CHECK(*--it == "3");
		CHECK(*--it == "2");
		CHECK(*--it == "1");
		CHECK(it == stringVector.begin());
		CHECK(it != stringVector.end());
	}

	SECTION("for loop by forward iterators") {
		std::ostringstream output;
		for (auto iter = stringVector.begin(); iter != stringVector.end(); ++iter)
		{
			output << *iter;
		}
		CHECK(output.str() == "12345");
	}
}

TEST_CASE("forward double iterator") {
	MyArray<double> doubleVector{ 18.356987, 0.0005, -565.3658 };
	SECTION("increment postfix iterator until the end") {
		auto it = doubleVector.begin();
		CHECK(*it++ == Approx(18.356987).margin(0.01));
		CHECK(*it++ == Approx(0.0005).margin(0.01));
		CHECK(*it++ == Approx(-565.3658).margin(0.01));
	}

	SECTION("increment prefix iterator until the end") {
		auto it = doubleVector.begin();
		CHECK(*it == Approx(18.356987).margin(0.01));
		CHECK(*++it == Approx(0.0005).margin(0.01));
		CHECK(*++it == Approx(-565.3658).margin(0.01));
		CHECK(++it == doubleVector.end());
		CHECK(it != doubleVector.begin());
	}

	SECTION("decrement postfix iterator until vector begin") {
		auto it = doubleVector.end();
		it--;
		CHECK(*it-- == Approx(-565.3658).margin(0.01));
		CHECK(*it-- == Approx(0.0005).margin(0.01));
		CHECK(*it == Approx(18.356987).margin(0.01));
		CHECK(it == doubleVector.begin());
		CHECK(it != doubleVector.end());
	}

	SECTION("decrement prefix iterator until begin") {
		auto it = doubleVector.end();
		CHECK(*--it == Approx(-565.3658).margin(0.01));
		CHECK(*--it == Approx(0.0005).margin(0.01));
		CHECK(*--it == Approx(18.356987).margin(0.01));
		CHECK(it == doubleVector.begin());
		CHECK(it != doubleVector.end());
	}

	SECTION("for loop by forward iterators") {
		std::ostringstream output;
		for (auto iter = doubleVector.begin(); iter != doubleVector.end(); ++iter)
		{
			output << *iter << '\n';
		}
		CHECK(output.str() == "18.357\n0.0005\n-565.366\n");
	}
}

TEST_CASE("reverse string iterator")
{
	MyArray<std::string> stringVector{ "1", "2", "3", "4", "5" };
	SECTION("increment postfix iterator until the rend") {
		auto it = stringVector.rbegin();
		CHECK(*it++ == "5");
		CHECK(*it++ == "4");
		CHECK(*it++ == "3");
		CHECK(*it++ == "2");
		CHECK(*it++ == "1");
		CHECK(it == stringVector.rend());
		CHECK(it != stringVector.rbegin());
	}

	SECTION("increment prefix iterator until the rend") {
		auto it = stringVector.rbegin();
		CHECK(*it == "5");
		CHECK(*++it == "4");
		CHECK(*++it == "3");
		CHECK(*++it == "2");
		CHECK(*++it == "1");
		CHECK(++it == stringVector.rend());
		CHECK(it != stringVector.rbegin());
	}

	SECTION("decrement postfix iterator until rbegin") {
		auto it = stringVector.rend();
		it--;
		CHECK(*it-- == "1");
		CHECK(*it-- == "2");
		CHECK(*it-- == "3");
		CHECK(*it-- == "4");
		CHECK(*it == "5");
		CHECK(it == stringVector.rbegin());
		CHECK(it != stringVector.rend());
	}

	SECTION("decrement prefix iterator until rbegin") {
		auto it = stringVector.rend();
		CHECK(*--it == "1");
		CHECK(*--it == "2");
		CHECK(*--it == "3");
		CHECK(*--it == "4");
		CHECK(*--it == "5");
		CHECK(it == stringVector.rbegin());
		CHECK(it != stringVector.rend());
	}

	SECTION("for loop by forward iterators") {
		std::ostringstream output;
		for (auto iter = stringVector.rbegin(); iter != stringVector.rend(); ++iter)
		{
			output << *iter;
		}
		CHECK(output.str() == "54321");
	}
}

TEST_CASE("reverse double iterator") {
	MyArray<double> doubleVector{ 17.158, -0.165, -0.001 };
	SECTION("increment postfix iterator until the rend") {
		auto it = doubleVector.rbegin();
		CHECK(*it++ == Approx(-0.001).margin(0.01));
		CHECK(*it++ == Approx(-0.165).margin(0.01));
		CHECK(*it++ == Approx(17.158).margin(0.01));
		CHECK(it == doubleVector.rend());
		CHECK(it != doubleVector.rbegin());
	}

	SECTION("increment prefix iterator until the rend") {
		auto it = doubleVector.rbegin();
		CHECK(*it == Approx(-0.001).margin(0.01));
		CHECK(*++it == Approx(-0.165).margin(0.01));
		CHECK(*++it == Approx(17.158).margin(0.01));
		CHECK(++it == doubleVector.rend());
		CHECK(it != doubleVector.rbegin());
	}

	SECTION("decrement postfix iterator until vector begin") {
		auto it = doubleVector.rend();
		it--;
		CHECK(*it-- == Approx(17.158).margin(0.01));
		CHECK(*it-- == Approx(-0.165).margin(0.01));
		CHECK(*it == Approx(-0.001).margin(0.01));
		CHECK(it == doubleVector.rbegin());
		CHECK(it != doubleVector.rend());
	}

	SECTION("decrement prefix iterator until begin") {
		auto it = doubleVector.rend();
		CHECK(*--it == Approx(17.158).margin(0.01));
		CHECK(*--it == Approx(-0.165).margin(0.01));
		CHECK(*--it == Approx(-0.001).margin(0.01));
		CHECK(it == doubleVector.rbegin());
		CHECK(it != doubleVector.rend());
	}

	SECTION("for loop by forward iterators") {
		std::ostringstream output;
		for (auto iter = doubleVector.rbegin(); iter != doubleVector.rend(); ++iter)
		{
			output << *iter << '\n';
		}
		CHECK(output.str() == "-0.001\n-0.165\n17.158\n");
	}
}

/*TEST_CASE("operator= with static_cast for l-value")
{
	MyArray<int> v1{1, 2 };
	MyArray<float> v2{ 14.8f, 29.5f };
	v2 = v1;
	CHECK(v2.GetSize() == 4);
	CHECK(v2[0] == "1");
	CHECK(v2[1] == "2");
	CHECK(v2[2] == "3");
	CHECK(v2[3] == "4");

	CHECK(v1.GetSize() == 4);
	CHECK(v1[0] == "1");
	CHECK(v1[1] == "2");
	CHECK(v1[2] == "3");
	CHECK(v1[3] == "4");
}*/

/*TEST_CASE("operator= with static_cast for r-value")
{
	MyArray<std::string> v = { "1", "2", "3", "4", "5", "6" };
	v = MyArray<std::string>({ "1", "2", "3", "4" });
	CHECK(v.GetSize() == 4);
	CHECK(v[0] == "1");
	CHECK(v[1] == "2");
	CHECK(v[2] == "3");
	CHECK(v[3] == "4");
}*/