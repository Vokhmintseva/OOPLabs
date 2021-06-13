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
	for (StringList::Const_reverse_iterator iter = strList.crbegin(); iter != strList.crend(); iter++)
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

TEST_CASE("insert element by forward iterator in the list of several elements")
{
	StringList strList;
	strList.AppendItem("1");
	strList.AppendItem("2");
	strList.AppendItem("3");
	strList.AppendItem("5");
	std::ostringstream output;
	
	SECTION("insert into list tail") {
		StringList::Iterator it = strList.begin();
		it++;
		it++;
		it++;
		strList.InsertItem(it, "4");
		for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); iter++)
		{
			output << iter->m_value;
		}
		CHECK(output.str() == "12345");
	}

	SECTION("insert into list head") {
		StringList::Const_iterator it = strList.cbegin();
		strList.InsertItem(it, "0");
		for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); iter++)
		{
			output << iter->m_value;
		}
		CHECK(output.str() == "01235");
	}

	SECTION("insert into past-the-last item") {
		StringList::Iterator it = strList.begin();
		it++;
		it++;
		it++;
		it++;
		strList.InsertItem(it, "6");
		for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); iter++)
		{
			output << iter->m_value;
		}
		CHECK(output.str() == "12356");
		it = strList.begin();
		CHECK(it->m_value == "1");
		it = strList.end();
		--it;
		CHECK(it->m_value == "6");
	}
}

TEST_CASE("insert element by forward iterator in the empty list")
{
	StringList strList;
	StringList::Const_iterator it = strList.begin();
	std::ostringstream output;

	SECTION("insert first element") {
		strList.InsertItem(it, "first elem");
		for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); iter++)
		{
			output << iter->m_value;
		}
		CHECK(output.str() == "first elem");
		CHECK(strList.GetCount() == 1);
		CHECK(!strList.IsEmpty());
		it = strList.begin();
		CHECK(it->m_value == "first elem");
	}

	SECTION("insert into empty list after increment of iterator") {
		it++;
		strList.InsertItem(it, "first elem");
		for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); iter++)
		{
			output << iter->m_value;
		}
		CHECK(output.str() == "first elem");
		CHECK(strList.GetCount() == 1);
		CHECK(!strList.IsEmpty());
		it = strList.begin();
		CHECK(it->m_value == "first elem");
	}
}

TEST_CASE("get not const iterator from const: constructor and converting operator")
{
	StringList strList;
	strList.PrependItem("1");
	StringList::Iterator iter1 = strList.begin();
	StringList::Const_iterator iter2(iter1);
	StringList::Const_iterator iter3 = iter1;
	CHECK(iter2->m_value == "1");
	CHECK(iter3->m_value == "1");
}


TEST_CASE("delete element by iterator in the list of several elements")
{
	StringList strList;
	strList.AppendItem("1");
	strList.AppendItem("2");
	strList.AppendItem("3");
	strList.AppendItem("4");
	StringList::Const_iterator it = strList.cbegin();
	std::ostringstream output;

	SECTION("delete from list tail") {
		it++;
		it++;
		it++;
		strList.DeleteItem(it);
		for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); iter++)
		{
			output << iter->m_value;
		}
		CHECK(output.str() == "123");
		CHECK(strList.GetCount() == 3);
		CHECK(!strList.IsEmpty());
		it = strList.cbegin();
		CHECK(it->m_value == "1");
		it = strList.cend();
		--it;
		CHECK(it->m_value == "3");
	}

	SECTION("delete from list head") {
		strList.DeleteItem(it);
		for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); iter++)
		{
			output << iter->m_value;
		}
		CHECK(output.str() == "234");
		CHECK(strList.GetCount() == 3);
		CHECK(!strList.IsEmpty());
		it = strList.cbegin();
		CHECK(it->m_value == "2");
		it = strList.cend();
		--it;
		CHECK(it->m_value == "4");
	}

	SECTION("delete from list middle") {
		++it;
		++it;
		strList.DeleteItem(it);
		for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); iter++)
		{
			output << iter->m_value;
		}
		CHECK(output.str() == "124");
		CHECK(strList.GetCount() == 3);
		CHECK(!strList.IsEmpty());
		it = strList.cbegin();
		CHECK(it->m_value == "1");
		it = strList.cend();
		--it;
		CHECK(it->m_value == "4");
	}
}

TEST_CASE("increment")
{
	StringList strList;
	strList.AppendItem("1");
	strList.AppendItem("2");
	strList.AppendItem("3");
	strList.AppendItem("4");
	StringList::Const_iterator it = strList.cbegin();
	it++;
	CHECK(it->m_value == "2");
	++it;
	it++;
	CHECK(it->m_value == "4");
	++it;
	CHECK(it == strList.cend());
	REQUIRE_THROWS_WITH(it++, "can't increment iterator after past end");
	REQUIRE_THROWS_WITH(++it, "can't increment iterator after past end");
}

TEST_CASE("decrement")
{
	StringList strList;
	strList.AppendItem("1");
	strList.AppendItem("2");
	strList.AppendItem("3");
	strList.AppendItem("4");
	StringList::Const_iterator it = strList.cend();
	it--;
	CHECK(it->m_value == "4");
	--it;
	it--;
	CHECK(it->m_value == "2");
	it--;
	CHECK(it == strList.cbegin());
	REQUIRE_THROWS_WITH(it--, "can't decrement iterator before begin");
	REQUIRE_THROWS_WITH(--it, "can't decrement iterator before begin");
}

/*TEST_CASE("insert element by forward iterator in the list of several elements")
{
	StringList strList;
	strList.AppendItem("1");
	strList.AppendItem("2");
	strList.AppendItem("3");
	strList.AppendItem("4");
	std::ostringstream output;



	SECTION("insert into list head") {
		StringList::Const_iterator it = strList.cbegin();
		strList.InsertItem(it, "0");
		for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); iter++)
		{
			output << iter->m_value;
		}
		CHECK(output.str() == "01234");
	}

	SECTION("insert into past-the-last item") {
		StringList::Iterator it = strList.begin();
		it++;
		it++;
		it++;
		it++;
		strList.InsertItem(it, "6");
		for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); iter++)
		{
			output << iter->m_value;
		}
		CHECK(output.str() == "12346");
		it = strList.begin();
		CHECK(it->m_value == "1");
		it = strList.end();
		--it;
		CHECK(it->m_value == "6");
	}
}

TEST_CASE("insert element by reverse iterator in the list of several elements")
{
	StringList strList;
	strList.AppendItem("1");
	strList.AppendItem("2");
	strList.AppendItem("3");
	strList.AppendItem("4");
	std::ostringstream output;

	SECTION("insert into list head") {
		StringList::Reverse_iterator it = strList.rbegin();
		strList.InsertItem(it, "0");
		for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); iter++)
		{
			output << iter->m_value;
		}
		CHECK(output.str() == "01234");
	}

	SECTION("insert into past-the-last item") {
		StringList::Iterator it = strList.begin();
		it++;
		it++;
		it++;
		it++;
		strList.InsertItem(it, "6");
		for (StringList::Const_iterator iter = strList.cbegin(); iter != strList.cend(); iter++)
		{
			output << iter->m_value;
		}
		CHECK(output.str() == "12346");
		it = strList.begin();
		CHECK(it->m_value == "1");
		it = strList.end();
		--it;
		CHECK(it->m_value == "6");
	}
}*/