// MyString_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include <iostream>
#include <string>
#include "../CMyString/MyString.h"

TEST_CASE("default constructor")
{
	MyString myStr;
	CHECK(myStr.GetLength() == 0);
	CHECK(myStr.GetStringData()[0] == '\0');
}

TEST_CASE("constructor: MyString(const char * pString)")
{
	char testStr[] = "Hello, World!";
	SECTION("construction string the same as original")
	{
		MyString myStr(testStr);
		CHECK(myStr.GetLength() == 13);
		CHECK(myStr.GetStringData()[13] == '\0');
		CHECK(strcmp(testStr, myStr.GetStringData()) == 0);
	}
	SECTION("construction string not from begin of original string")
	{
		MyString myStr(&testStr[3]);
		CHECK(myStr.GetLength() == 10);
		CHECK(myStr.GetStringData()[10] == '\0');
		char expectedStr[] = "lo, World!";
		CHECK(strcmp(expectedStr, myStr.GetStringData()) == 0);
	}
}

TEST_CASE("constructor: MyString(const char * pString, size_t length)")
{
	SECTION("constructing string-1")
	{
		char testStr[] = "Calculator";
		MyString myStr(testStr, 4);
		CHECK(myStr.GetLength() == 4);
		CHECK(myStr.GetStringData()[4] == '\0');
		char expectedStr[] = "Calc";
		CHECK(strcmp(expectedStr, myStr.GetStringData()) == 0);
	}
	SECTION("constructing string-2")
	{
		char testStr[] = "Calcul\0ator";
		MyString myStr(&testStr[2], 7);
		CHECK(myStr.GetLength() == 7);
		CHECK(myStr.GetStringData()[7] == '\0');
		CHECK(MyString("lcul\0at", 7) == myStr);
	}
	SECTION("constructing string with length 0")
	{
		char testStr[] = "Calculator";
		MyString myStr(testStr, 0);
		CHECK(myStr.GetLength() == 0);
		CHECK(myStr.GetStringData()[0] == '\0');

	}
	SECTION("constructing string that contains null code in the middle")
	{
		char testStr[] = "Calcul\0ator";
		MyString myStr(testStr, 9);
		CHECK(myStr.GetLength() == 9);
		CHECK(myStr.GetStringData()[9] == '\0');
		CHECK(MyString("Calcul\0at", 9) == myStr);
	}
}

TEST_CASE("constructor: MyString(std::string const& stlString)")
{
	SECTION("construction not empty string")
	{
		std::string testStr = "Hello World!";
		MyString myStr(testStr);
		CHECK(myStr.GetLength() == 12);
		CHECK(myStr.GetStringData()[12] == '\0');
		CHECK(strcmp(testStr.c_str(), myStr.GetStringData()) == 0);
	}
	SECTION("construction empty string")
	{
		std::string testStr;
		MyString myStr(testStr);
		CHECK(myStr.GetLength() == 0);
		CHECK(myStr.GetStringData()[0] == '\0');
		CHECK(strcmp(testStr.c_str(), myStr.GetStringData()) == 0);
	}
}

TEST_CASE("copy constructor")
{
	SECTION("copying not empty string")
	{
		MyString originalStr("Hello\0World!", 12);
		MyString copiedStr(originalStr);
		CHECK(copiedStr.GetLength() == 12);
		CHECK(copiedStr.GetStringData()[12] == '\0');
		CHECK(MyString("Hello\0World!", 12) == copiedStr);
	}
	SECTION("copying empty string")
	{
		MyString originalStr;
		MyString copiedStr(originalStr);
		CHECK(copiedStr.GetLength() == 0);
		CHECK(copiedStr.GetStringData()[0] == '\0');
	}
}

TEST_CASE("move constructor")
{
	SECTION("copying not empty string")
	{
		MyString originalStr = MyString("Construct\0or", 12);
		MyString newStr(std::move(originalStr));
		CHECK(newStr.GetLength() == 12);
		CHECK(newStr.GetStringData()[12] == '\0');
		CHECK(originalStr.GetLength() == 0);
		CHECK(originalStr.GetStringData() == nullptr);
	}
}

TEST_CASE("method Clear")
{
	MyString myStr("Computer");
	CHECK(myStr.GetLength() == 8);
	CHECK(myStr.GetStringData()[8] == '\0');
	myStr.Clear();
	CHECK(myStr.GetLength() == 0);
	CHECK(myStr.GetStringData()[0] == '\0');
}

TEST_CASE("method SubString")
{
	MyString myStr("Computer");
	SECTION("creating substring-1")
	{
		MyString subStr = myStr.SubString(0, 5);
		CHECK(subStr.GetLength() == 5);
		CHECK(subStr.GetStringData()[5] == '\0');
        CHECK(MyString("Compu") == subStr);
	}
	SECTION("creating substring-2")
	{
		MyString subStr = myStr.SubString(7, 1);
		CHECK(subStr.GetLength() == 1);
		CHECK(subStr.GetStringData()[1] == '\0');
		CHECK(MyString("r") == subStr);
	}
	SECTION("creating empty substring")
	{
		MyString subStr = myStr.SubString(8, 0);
		CHECK(subStr.GetLength() == 0);
		CHECK(subStr.GetStringData()[0] == '\0');
		CHECK(MyString("") == subStr);
	}
	SECTION("incorrect arguments given")
	{
		REQUIRE_THROWS_AS(myStr.SubString(0, 9), std::out_of_range);
		REQUIRE_THROWS_AS(myStr.SubString(2, 7), std::out_of_range);
		REQUIRE_THROWS_AS(myStr.SubString(7, 2), std::out_of_range);
		REQUIRE_THROWS_AS(myStr.SubString(9, 1), std::out_of_range);
	}
}

TEST_CASE("operator ==")
{
	SECTION("equial not empty strings")
	{
		MyString myStr1("Comp\0uter", 9);
		MyString myStr2("Comp\0uter", 9);
		CHECK(myStr1 == myStr2);
	}
	SECTION("equial empty strings")
	{
		MyString myStr1;
		MyString myStr2;
		CHECK(myStr1 == myStr2);
	}
	SECTION("not equial strings")
	{
		MyString myStr1("Comp\0uter", 9);
		MyString myStr2("Computer");
		CHECK((myStr1 == myStr2) == false);
	}
	SECTION("compare variable to itself")
	{
		MyString myStr1("Comp\0uter", 9);
		CHECK(myStr1 == myStr1);
	}
}

TEST_CASE("operator !=")
{
	SECTION("not equial not empty strings")
	{
		MyString myStr1("Alloc\0ation", 11);
		MyString myStr2("Alloc\0ation");
		CHECK(myStr1 != myStr2);
	}
	SECTION("equial empty strings")
	{
		MyString myStr1;
		MyString myStr2;
		CHECK((myStr1 != myStr2) == false);
	}
	SECTION("not equial strings")
	{
		size_t len = 9;
		MyString myStr1("Alloc\0ation", 11);
		MyString myStr2("Computer");
		CHECK((myStr1 != myStr2) == true);
	}
}

TEST_CASE("operator =")
{
	SECTION("the value of variable is set to another variable - 1")
	{
		MyString myStr1("Alloc\0ation", 11);
		MyString myStr2 = myStr1;
		CHECK(myStr1 == myStr2);
		CHECK(myStr2.GetLength() == 11);
		CHECK(myStr2.GetStringData()[11] == '\0');
	}
	SECTION("empty string is set to another variable")
	{
		MyString myStr1;
		MyString myStr2 = myStr1;
		CHECK(myStr1 == myStr2);
		CHECK(myStr2.GetLength() == 0);
		CHECK(myStr2.GetStringData()[0] == '\0');
	}
	SECTION("the value of variable is set to another variable - 2")
	{
		MyString myStr1("Week");
		MyString myStr2 = myStr1;
		CHECK(myStr1 == myStr2);
		CHECK(myStr2.GetLength() == 4);
		CHECK(myStr2.GetStringData()[4] == '\0');
	}
	SECTION("the value of variable is set to another variable - 3")
	{
		std::string myStr1 = "day";
		MyString myStr2 = myStr1;
		CHECK(myStr1 == myStr2);
		CHECK(myStr2.GetLength() == 3);
		CHECK(myStr2.GetStringData()[3] == '\0');
	}
	SECTION("the value of variable is set to itself")
	{
		MyString myStr1 = "day";
		myStr1 = myStr1;
		CHECK(myStr1 == myStr1);
		CHECK(myStr1.GetLength() == 3);
		CHECK(myStr1.GetStringData()[3] == '\0');
	}
}

TEST_CASE("operator +=")
{
	SECTION("adding not empty string")
	{
		MyString myStr1("Alloc\0ation\0", 12);
		MyString myStr2("Reallocation");
		myStr1 += myStr2;
		CHECK(myStr1 == MyString("Alloc\0ation\0Reallocation", 24));
		CHECK(myStr1.GetStringData()[24] == '\0');
	}
	SECTION("adding not empty string to empty one")
	{
		MyString myStr1;
		MyString myStr2("Reallocation");
		myStr1 += myStr2;
		CHECK(myStr1 == "Reallocation");
		CHECK(myStr1.GetStringData()[12] == '\0');
	}
	 SECTION("adding empty string to not empty one")
	 {
		 MyString myStr1("Reallocation");
		 MyString myStr2;
		 myStr1 += myStr2;
		 CHECK(myStr1 == "Reallocation");
		 CHECK(myStr1.GetStringData()[12] == '\0');
	 }
	 SECTION("adding empty string to empty string")
	 {
		 MyString myStr1;
		 MyString myStr2;
		 myStr1 += myStr2;
		 CHECK(myStr1 == "");
		 CHECK(myStr1.GetStringData()[0] == '\0');
	 }
	 SECTION("adding several strings")
	 {
		 MyString myStr1("Allocation");
		 MyString myStr2("_adding_");
		 MyString myStr3("Reallocation");
		 (myStr1 += myStr2) += myStr3;
		 CHECK(myStr1 == "Allocation_adding_Reallocation");
		 CHECK(myStr1.GetStringData()[30] == '\0');
	 }
}

TEST_CASE("operator +")
{
	SECTION("MyString + MyString")
	{
		MyString myStr1("Allocation");
		MyString myStr2("Reallocation");
		MyString newStr = myStr1 + myStr2;
		CHECK(newStr == MyString("AllocationReallocation"));
		CHECK(newStr.GetStringData()[22] == '\0');
	}
	SECTION("std::string + MyString")
	{
		std::string myStr1 = "Allocation";
		MyString myStr2("Reallocation");
		MyString newStr = myStr1 + myStr2;
		CHECK(newStr == "AllocationReallocation");
		CHECK(newStr.GetStringData()[22] == '\0');
	}
	SECTION("empty std::string + MyString")
	{
		std::string myStr1;
		MyString myStr2("Reallocation");
		MyString newStr = myStr1 + myStr2;
		CHECK(newStr == "Reallocation");
		CHECK(newStr.GetStringData()[12] == '\0');
	}
	SECTION("const char * + MyString")
	{
		const char * myStr1 = "Allocation";
		MyString myStr2("Reallocation");
		MyString newStr = myStr1 + myStr2;
		CHECK(newStr == "AllocationReallocation");
		CHECK(newStr.GetStringData()[22] == '\0');
	}
}

TEST_CASE("operator []")
{
	SECTION("access to symbols of string")
	{
		MyString myStr("Ye\0ar", 5);
		CHECK(myStr[0] == 'Y');
		CHECK(myStr[1] == 'e');
		CHECK(myStr[2] == '\0');
		CHECK(myStr[3] == 'a');
		CHECK(myStr[4] == 'r');
		REQUIRE_THROWS_AS(myStr[5], std::out_of_range);
		myStr[0] = 'w';
		myStr[1] = 'e';
		myStr[2] = 'e';
		myStr[3] = 'k';
		myStr[4] = 'r';
		REQUIRE_THROWS_AS(myStr[5] = 'e', std::out_of_range);
		CHECK(myStr == MyString("weekr"));
	}
	SECTION("access to symbol of empty string")
	{
		MyString myStr;
		REQUIRE_THROWS_AS(myStr[0], std::out_of_range);
	}
}

TEST_CASE("operators <, >, ==, !=, <=, >=")
{
	MyString myStr1("Cat");
	MyString myStr2("Cats");
	CHECK(myStr1 < myStr2);
	CHECK(!(myStr1 > myStr2));
	CHECK(!(myStr1 == myStr2));
	CHECK(myStr1 != myStr2);
	CHECK(myStr1 <= myStr2);
	CHECK(!(myStr1 >= myStr2));
	
	MyString myStr3("Cat");
	MyString myStr4("Cat");
	CHECK(!(myStr3 < myStr4));
	CHECK(!(myStr3 > myStr4));
	CHECK(myStr3 == myStr4);
	CHECK(!(myStr3 != myStr4));
	CHECK(myStr3 <= myStr4);
	CHECK(myStr3 >= myStr4);

	MyString myStr5("Cat");
	MyString myStr6("cat");
	CHECK(myStr5 < myStr6);
	CHECK(!(myStr5 > myStr6));
	CHECK(!(myStr5 == myStr6));
	CHECK(myStr5 != myStr6);
	CHECK(myStr5 <= myStr6);
	CHECK(!(myStr5 >= myStr6));

	MyString myStr7("C\0at", 4);
	MyString myStr8("C\0ats", 5);
	CHECK(myStr7 < myStr8);
	CHECK(!(myStr7 > myStr8));
	CHECK(!(myStr7 == myStr8));
	CHECK(myStr7 != myStr8);
	CHECK(myStr7 <= myStr8);
	CHECK(!(myStr7 >= myStr8));

	MyString myStr9;
	MyString myStr10;
	CHECK(!(myStr9 < myStr10));
	CHECK(!(myStr9 > myStr10));
	CHECK(myStr9 == myStr10);
	CHECK(!(myStr9 != myStr10));
	CHECK(myStr9 <= myStr10);
	CHECK(myStr9 >= myStr10);

	MyString myStr11;
	MyString myStr12("cat");
	CHECK(myStr11 < myStr12);
	CHECK(!(myStr11 > myStr12));
	CHECK(!(myStr11 == myStr12));
	CHECK(myStr11 != myStr12);
	CHECK(myStr11 <= myStr12);
	CHECK(!(myStr11 >= myStr12));

	MyString myStr13("c");
	MyString myStr14;
	CHECK(!(myStr13 < myStr14));
	CHECK(myStr13 > myStr14);
	CHECK(!(myStr13 == myStr14));
	CHECK(myStr13 != myStr14);
	CHECK(!(myStr13 <= myStr14));
	CHECK(myStr13 >= myStr14);

	MyString myStr15("C\0ats", 5);
	MyString myStr16("C\0at", 4);
	CHECK(myStr15 > myStr16);
	CHECK(!(myStr15 < myStr16));
	CHECK(!(myStr15 == myStr16));
	CHECK(myStr15 != myStr16);
	CHECK(myStr15 >= myStr16);
	CHECK(!(myStr15 <= myStr16));
}

TEST_CASE("operator <<")
{
	MyString str1("Cat");
	std::ostringstream output;
	output << str1;
	CHECK(output.str() == "Cat");

	MyString str2("Ca\0t", 4);
	output.str("");
	output << str2;
	CHECK(output.str() == "Cat");

	MyString str3;
	output.str("");
	output << str3;
	CHECK(output.str() == "");

	MyString str4("The London is the capital of GB\n");
	output.str("");
	output << str4;
	CHECK(output.str() == "The London is the capital of GB\n");

	MyString str5("The\0London\0is\0the\0capital of GB\n");
	output.str("");
	output << str5;
	CHECK(output.str() == "The\0London\0is\0the\0capital of GB\n");
}

TEST_CASE("Operator >>")
{
	MyString myStr1;
	std::istringstream input;
	input.str("Dog");
	input >> myStr1;
	CHECK(myStr1 == MyString("Dog"));
	CHECK(myStr1.GetStringData()[3] == '\0');
	CHECK(myStr1.GetLength() == 3);

	input.str("");
	MyString myStr2("Dog\n");
	input >> myStr2;
	CHECK(myStr2 == MyString("Dog\n"));
	CHECK(myStr2.GetStringData()[4] == '\0');
	CHECK(myStr2.GetLength() == 4);

	input.str("");
	MyString myStr3("Dog, cat and fox");
	input >> myStr3;
	CHECK(myStr3 == MyString("Dog, cat and fox"));
	CHECK(myStr3.GetStringData()[16] == '\0');
	CHECK(myStr3.GetLength() == 16);

	input.str("");
	MyString myStr4("Dog, cat and fox\nThe London is the capital of GB\n");
	input >> myStr4;
	CHECK(myStr4 == MyString("Dog, cat and fox\nThe London is the capital of GB\n"));
	CHECK(myStr4.GetStringData()[49] == '\0');
	CHECK(myStr4.GetLength() == 49);

	input.str("");
	MyString myStr5;
	input >> myStr5;
	CHECK(myStr5.GetStringData()[0] == '\0');
	CHECK(myStr5.GetLength() == 0);
}

TEST_CASE("move operator =")
{
	MyString originalStr1 = MyString("Construct\0or", 12);
	MyString newStr1;
	newStr1 = std::move(originalStr1);
	CHECK(newStr1.GetLength() == 12);
	CHECK(newStr1.GetStringData()[12] == '\0');
	CHECK(newStr1 == MyString("Construct\0or", 12));
	CHECK(originalStr1.GetLength() == 0);
	CHECK(originalStr1.GetStringData() == nullptr);

	MyString newStr2;
	newStr2 = MyString();
	CHECK(newStr2.GetLength() == 0);
	CHECK(newStr2.GetStringData()[0] == '\0');

	MyString newStr3;
	newStr3 = MyString("Cat and dog");
	CHECK(newStr3 == MyString("Cat and dog"));
	CHECK(newStr3.GetLength() == 11);
	CHECK(newStr3.GetStringData()[11] == '\0');
}

TEST_CASE("forward not const iterator")
{
	MyString originalStr = MyString("Codes");
	auto it = originalStr.begin();
	*originalStr.begin() = 'N';
	it++;
	CHECK(*it == 'o');
	++it;
	CHECK(*it == 'd');
	it++;
	CHECK(*it == 'e');
	++it;
	*it = 'e';
	CHECK(*it == 'e');
	it++;
	CHECK(it == originalStr.end());
	CHECK(*it == '\0');
	CHECK(originalStr == MyString("Nodee"));
}

TEST_CASE("forward const iterator")
{
	const MyString originalStr = MyString("Codes");
	auto it = originalStr.begin();
	CHECK(*it == 'C');
	it++;
	CHECK(*it == 'o');
	++it;
	CHECK(*it == 'd');
	it++;
	CHECK(*it == 'e');
	++it;
	CHECK(*it == 's');
	it++;
	CHECK(it == originalStr.end());
	CHECK(originalStr == MyString("Codes"));
}