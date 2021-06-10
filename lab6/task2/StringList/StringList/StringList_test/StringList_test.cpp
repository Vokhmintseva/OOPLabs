// StringList_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define CATCH_CONFIG_MAIN
#include "../../../../../catch.hpp"
#include <iostream>
#include "../StringList/StringList.h"

TEST_CASE("create empty stringList")
{
	StringList strList;
	CHECK(strList.GetCount() == 0);
	CHECK(strList.IsEmpty());
}

TEST_CASE("method append")
{
	StringList strList;
	strList.AppendItem("firstString");
	strList.AppendItem("secondString");
	strList.AppendItem("thirdString");
	CHECK(strList.GetCount() == 3);
	CHECK(!strList.IsEmpty());
    CHECK(strList.GeatHeadValue() == "firstString");
	CHECK(strList.GeatTailValue() == "thirdString");
}

TEST_CASE("method prepend")
{
	StringList strList;
	strList.PrependItem("thirdString");
	strList.PrependItem("secondString");
	strList.PrependItem("firstString");
	CHECK(strList.GetCount() == 3);
	CHECK(!strList.IsEmpty());
	CHECK(strList.GeatHeadValue() == "firstString");
	CHECK(strList.GeatTailValue() == "thirdString");
}

TEST_CASE("method Clear")
{
	StringList strList;
	strList.PrependItem("thirdString");
	strList.PrependItem("secondString");
	strList.PrependItem("firstString");
	strList.Clear();
	CHECK(strList.GetCount() == 0);
	CHECK(strList.IsEmpty());
}

TEST_CASE("loops")
{
	StringList strList;
	strList.PrependItem("thirdString");
	strList.PrependItem("secondString");
	strList.PrependItem("firstString");
	std::ostringstream output;
	
	SECTION("'range based for' loop")
	{
		for (auto&& item : strList)
		{
			output << item.m_value << std::endl;
		}
		CHECK(output.str() == "firstString\nsecondString\nthirdString\n");
		for (auto&& item : strList)
		{
			item.m_value = "new_value";
		}
		output.str("");
		for (auto&& item : strList)
		{
			output << item.m_value << std::endl;
		}
		CHECK(output.str() == "new_value\nnew_value\nnew_value\n");
	}

	SECTION("'for' loop by not const iterator")
	{
		for (StringList::Iterator iter = strList.begin(); iter != strList.end(); ++iter)
		{
			output << iter->m_value << std::endl;
		}
		for (StringList::Iterator iter = strList.begin(); iter != strList.end(); ++iter)
		{
			iter->m_value = "new_string";
		}
		for (StringList::Iterator iter = strList.begin(); iter != strList.end(); ++iter)
		{
			output << iter->m_value << std::endl;
		}
		CHECK(output.str() == "firstString\nsecondString\nthirdString\nnew_string\nnew_string\nnew_string\n");
	}

	SECTION("'for' loop by const iterator")
	{
		for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); ++iter)
		{
			output << iter->m_value << std::endl;
		}
		CHECK(output.str() == "firstString\nsecondString\nthirdString\n");
	}

	SECTION("'for' loop by reverse iterator")
	{
		for (StringList::Reverse_iterator iter = strList.rbegin(); iter != strList.rend(); iter++)
		{
			output << iter->m_value << std::endl;
		}
		CHECK(output.str() == "thirdString\nsecondString\nfirstString\n");
		output.str("");
		for (StringList::Iterator iter = strList.begin(); iter != strList.end(); ++iter)
		{
			iter->m_value = "new_string";
		}
		for (StringList::Reverse_iterator iter = strList.rbegin(); iter != strList.rend(); iter++)
		{
			output << iter->m_value << std::endl;
		}
		CHECK(output.str() == "new_string\nnew_string\nnew_string\n");
	}

	SECTION("'for' loop by const reverse iterator")
	{
		for (StringList::Const_reverse_iterator iter = strList.crbegin(); iter != strList.crend(); iter++)
		{
			output << iter->m_value << std::endl;
		}
		CHECK(output.str() == "thirdString\nsecondString\nfirstString\n");
	}
}

TEST_CASE("Iterators over empty StringList ")
{
	StringList emptyStrList;
	std::ostringstream output;
	SECTION("'range based for' loop over empty string list")
	{
		for (auto&& item : emptyStrList)
		{
			output << item.m_value << std::endl;
		}
		CHECK(output.str() == "");
	}

	SECTION("'for' loop by not const iterator")
	{
		for (StringList::Iterator iter = emptyStrList.begin(); iter != emptyStrList.end(); ++iter)
		{
			output << iter->m_value << std::endl;
		}
		CHECK(output.str() == "");
		CHECK(emptyStrList.begin() == emptyStrList.end());
	}

	SECTION("'for' loop by const iterator")
	{
		for (StringList::Const_iterator iter = emptyStrList.cbegin(); iter != emptyStrList.cend(); ++iter)
		{
			output << iter->m_value << std::endl;
		}
		CHECK(output.str() == "");
		CHECK(emptyStrList.cbegin() == emptyStrList.cend());
	}

	SECTION("'for' loop by reverse iterator")
	{
		for (StringList::Reverse_iterator iter = emptyStrList.rbegin(); iter != emptyStrList.rend(); iter++)
		{
			output << iter->m_value << std::endl;
		}
		CHECK(output.str() == "");
		CHECK(emptyStrList.rbegin() == emptyStrList.rend());
	}

	SECTION("'for' loop by const reverse iterator")
	{
		for (StringList::Const_reverse_iterator iter = iter = emptyStrList.crbegin(); iter != emptyStrList.crend(); iter++)
		{
			output << iter->m_value << std::endl;
		}
		CHECK(output.str() == "");
		CHECK(emptyStrList.crbegin() == emptyStrList.crend());
	}
}

TEST_CASE("method append and prepend")
{
	StringList strList;
	strList.PrependItem("3");
	strList.AppendItem("4");
	strList.PrependItem("2");
	strList.AppendItem("5");
	strList.PrependItem("1");
	CHECK(strList.GetCount() == 5);
	CHECK(!strList.IsEmpty());
	CHECK(strList.GeatHeadValue() == "1");
	CHECK(strList.GeatTailValue() == "5");
	std::ostringstream output;

	for (auto&& item : strList)
	{
		output << item.m_value;
	}
	CHECK(output.str() == "12345");
	output.str("");
	for (StringList::Const_reverse_iterator iter = iter = strList.crbegin(); iter != strList.crend(); iter++)
	{
		output << iter->m_value;
	}
	CHECK(output.str() == "54321");
}

TEST_CASE("one string appended")
{
	StringList strList;
	strList.AppendItem("One");
	CHECK(strList.GetCount() == 1);
	CHECK(!strList.IsEmpty());
	std::ostringstream output;

	for (auto&& item : strList)
	{
		output << item.m_value;
	}
	CHECK(output.str() == "One");
	output.str("");
	for (StringList::Const_reverse_iterator iter = strList.crbegin(); iter != strList.crend(); iter++)
	{
		output << iter->m_value;
	}
	CHECK(output.str() == "One");
	StringList::Reverse_iterator it = strList.rbegin();
	output.str("");
	it->m_value = "Another one";
	for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); iter++)
	{
		output << iter->m_value;
	}
	CHECK(output.str() == "Another one");
}

TEST_CASE("one string prepended")
{
	StringList strList;
	strList.PrependItem("One");
	CHECK(strList.GetCount() == 1);
	CHECK(!strList.IsEmpty());
	std::ostringstream output;

	for (auto&& item : strList)
	{
		output << item.m_value;
	}
	CHECK(output.str() == "One");
	output.str("");
	for (StringList::Const_reverse_iterator iter = strList.crbegin(); iter != strList.crend(); iter++)
	{
		output << iter->m_value;
	}
	CHECK(output.str() == "One");
	StringList::Reverse_iterator it = strList.rbegin();
	output.str("");
	it->m_value = "Another one";
	for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); iter++)
	{
		output << iter->m_value;
	}
	CHECK(output.str() == "Another one");
}

/*TEST_CASE("insert element by iterator")
{
	StringList strList;
	strList.AppendItem("1");
	strList.AppendItem("2");
	strList.AppendItem("3");
	strList.AppendItem("5");

	StringList::Iterator it = strList.begin();
	it++;
	it++;
	it++;
	strList.InsertItem(it, "4");
	std::ostringstream output;
	for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); iter++)
	{
		output << iter->m_value;
	}
	CHECK(output.str() == "12345");
}*/