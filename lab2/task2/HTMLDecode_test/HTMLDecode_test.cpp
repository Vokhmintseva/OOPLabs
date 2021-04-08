// HTMLDecode_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <sstream>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"
#include "../HTMLDecode/HTMLDecode/Decode.h"

SCENARIO("Decoding any string")
{
	std::string anyStr = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	REQUIRE(HtmlDecode(anyStr) == "Cat <says> \"Meow\". M&M's");
}

SCENARIO("Decoding any string2")
{
	std::string anyStr = "Cat &lt;&lt;&lt;says&gt;&gt;&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	REQUIRE(HtmlDecode(anyStr) == "Cat <<<says>>> \"Meow\". M&M's");
}

SCENARIO("Decoding any string3")
{
	std::string anyStr = "&apos;&apos;Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s&apos;&apos;";
	REQUIRE(HtmlDecode(anyStr) == "''Cat <says> \"Meow\". M&M's''");
}

SCENARIO("Decoding any string4")
{
	std::string anyStr = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp";
	REQUIRE(HtmlDecode(anyStr) == "Cat <says> \"Meow\". M&amp");
}

SCENARIO("Decoding any string5")
{
	std::string anyStr = "The lakes are considered to contain about half of the world’s fresh water.";
	REQUIRE(HtmlDecode(anyStr) == "The lakes are considered to contain about half of the world’s fresh water.");
}

SCENARIO("Decoding empty string")
{
	std::ostringstream output;
	WHEN("Empty input string")
	{
		std::istringstream input("");
		THEN("output stream is also empty")
		{
			DecodeLines(input, output);
			CHECK(output.str().empty());
			CHECK(input.eof());
		}
	}
}

SCENARIO("Decoding several strings")
{
	std::ostringstream output;
	WHEN("Empty input string")
	{
		std::istringstream input("");
		THEN("output stream is also empty")
		{
			DecodeLines(input, output);
			CHECK(output.str().empty());
			CHECK(input.eof());
		}
	}

	WHEN("Decoding several strings")
	{
		std::istringstream input("&quot;input&quot; &apos;stream&apos; &lt;contains&gt; &amp;some lines&amp;\n &apos;&apos;input stream&apos;&apos; contains some lines&quot;&apos;&lt;&gt;&amp;\n");
		std::ostringstream output;
		THEN("output stream contains EOL in the end as well")
		{
			DecodeLines(input, output);
			CHECK(output.str() == "\"input\" 'stream' <contains> &some lines&\n ''input stream'' contains some lines\"'<>&\n");
			CHECK(input.eof());
		}
	}

	WHEN("input stream contains empty lines")
	{
		std::istringstream input("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s\n\nCat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");
		THEN("output stream contains empty lines as well")
		{
			DecodeLines(input, output);
			CHECK(output.str() == "Cat <says> \"Meow\". M&M's\n\nCat <says> \"Meow\". M&M's");
			CHECK(input.eof());
		}
	}
}
