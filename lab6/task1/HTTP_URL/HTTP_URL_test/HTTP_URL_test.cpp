// HTTP_URL_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../HTTP_URL/HttpUrl.h"
#include "../HTTP_URL/UrlParsingError.h"
#include "../../../../catch.hpp"

TEST_CASE("full url in low letters")
{
	HttpUrl url("http://testurl.ru:8025/image.png/");
	CHECK(url.GetURL() == "http://testurl.ru:8025/image.png/");
	CHECK(url.GetProtocol() == Protocol::HTTP);
	CHECK(url.GetPort() == 8025);
	CHECK(url.GetDomain() == "testurl.ru");
	CHECK(url.GetDocument() == "/image.png/");
}

TEST_CASE("full url in capital letters")
{
	HttpUrl url("https://TESTURL.RU:8025/image.png/");
	CHECK(url.GetURL() == "https://testurl.ru:8025/image.png/");
	CHECK(url.GetProtocol() == Protocol::HTTPS);
	CHECK(url.GetPort() == 8025);
	CHECK(url.GetDomain() == "testurl.ru");
	CHECK(url.GetDocument() == "/image.png/");
}

TEST_CASE("url without port")
{
	SECTION("url without port - http")
	{
		HttpUrl url("http://testurl.ru/image.png/");
		CHECK(url.GetURL() == "http://testurl.ru/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "testurl.ru");
		CHECK(url.GetDocument() == "/image.png/");
	}
	SECTION("url without port - https")
	{
		HttpUrl url("https://testurl.ru/image.png/");
		CHECK(url.GetURL() == "https://testurl.ru/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 443);
		CHECK(url.GetDomain() == "testurl.ru");
		CHECK(url.GetDocument() == "/image.png/");
	}
	SECTION("url without 0 port - https")
	{
		HttpUrl url("https://testurl.ru:0/image.png/");
		CHECK(url.GetURL() == "https://testurl.ru:0/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 0);
		CHECK(url.GetDomain() == "testurl.ru");
		CHECK(url.GetDocument() == "/image.png/");
	}
	SECTION("url with port 65535 - https")
	{
		HttpUrl url("https://testurl.ru:65535/image.png/");
		CHECK(url.GetURL() == "https://testurl.ru:65535/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 65535);
		CHECK(url.GetDomain() == "testurl.ru");
		CHECK(url.GetDocument() == "/image.png/");
	}
	SECTION("ip address")
	{
		HttpUrl url("https://127.0.0.1:65535/image.png/");
		CHECK(url.GetURL() == "https://127.0.0.1:65535/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 65535);
		CHECK(url.GetDomain() == "127.0.0.1");
		CHECK(url.GetDocument() == "/image.png/");
	}
	SECTION("ip address - 2")
	{
		HttpUrl url("https://255.255.255.255:65535/image.png/");
		CHECK(url.GetURL() == "https://255.255.255.255:65535/image.png/");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 65535);
		CHECK(url.GetDomain() == "255.255.255.255");
		CHECK(url.GetDocument() == "/image.png/");
	}
}

TEST_CASE("url without document")
{
	HttpUrl url("https://test.com:8025/");
	CHECK(url.GetURL() == "https://test.com:8025");
	CHECK(url.GetProtocol() == Protocol::HTTPS);
	CHECK(url.GetPort() == 8025);
	CHECK(url.GetDomain() == "test.com");
	CHECK(url.GetDocument() == "/");
}

TEST_CASE("invalid url in capital letters")
{
	REQUIRE_THROWS_WITH(HttpUrl("htt://invalirurl:8025/testdocument/"), "invalid url");
	REQUIRE_THROWS_WITH(HttpUrl("https:/invalirurl:8025/testdocument/"), "invalid url");
	REQUIRE_THROWS_WITH(HttpUrl("https://invalirurl:802/testdocument/"), "invalid url");
	REQUIRE_THROWS_WITH(HttpUrl("https://invalirurl8025/testdocument/"), "invalid url");
	REQUIRE_THROWS_WITH(HttpUrl("https:invalirurl:8025/testdocument/"), "invalid url");
	REQUIRE_THROWS_WITH(HttpUrl("https://invalirurl/8025/testdocument/"), "invalid url");
	REQUIRE_THROWS_WITH(HttpUrl("https://invalidurl.com:65536/testdocument/"), "invalid port value");
}

TEST_CASE("url constructor with 3 parameters")
{
	SECTION("url with domain and document")
	{
		HttpUrl url("test.com", "image");
		CHECK(url.GetURL() == "http://test.com/image");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/image");
	}
	SECTION("url with domain, document and protocol")
	{
		HttpUrl url("test.com", "/image.png", Protocol::HTTP);
		CHECK(url.GetURL() == "http://test.com/image.png");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/image.png");
	}
	SECTION("url with domain, document and protocol")
	{
		HttpUrl url("test.com", "/image.png", Protocol::HTTP);
		CHECK(url.GetURL() == "http://test.com/image.png");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/image.png");
	}
	SECTION("url with domain, document and protocol")
	{
		HttpUrl url("test.ru", "/path/to/document/", Protocol::HTTP);
		CHECK(url.GetURL() == "http://test.ru/path/to/document/");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "test.ru");
		CHECK(url.GetDocument() == "/path/to/document/");
	}
	SECTION("invalid parameters")
	{
		REQUIRE_THROWS_WITH(HttpUrl("test.ru", "", Protocol::HTTP), "invalid url parameters");
		REQUIRE_THROWS_WITH(HttpUrl("", "path", Protocol::HTTP), "invalid url parameters");
		REQUIRE_THROWS_WITH(HttpUrl("", "path"), "invalid url parameters");
	}
}

TEST_CASE("url constructor with 4 parameters")
{
	SECTION("url with domain, document, protocol, port")
	{
		HttpUrl url("test.com", "path/to/image.png", Protocol::HTTP, 8080);
		CHECK(url.GetURL() == "http://test.com:8080/path/to/image.png");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 8080);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/path/to/image.png");
	}
	SECTION("url with domain, document, protocol, port")
	{
		HttpUrl url("test.com", "/image.png", Protocol::HTTPS, 80);
		CHECK(url.GetURL() == "https://test.com/image.png");
		CHECK(url.GetProtocol() == Protocol::HTTPS);
		CHECK(url.GetPort() == 80);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/image.png");
	}
	SECTION("url with domain, document, protocol, port")
	{
		HttpUrl url("test.com", "/image.png", Protocol::HTTP, 8080);
		CHECK(url.GetURL() == "http://test.com:8080/image.png");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 8080);
		CHECK(url.GetDomain() == "test.com");
		CHECK(url.GetDocument() == "/image.png");
	}
	SECTION("url with domain, document, protocol, port")
	{
		HttpUrl url("test.ru", "/path/to/document/", Protocol::HTTP, 0);
		CHECK(url.GetURL() == "http://test.ru:0/path/to/document/");
		CHECK(url.GetProtocol() == Protocol::HTTP);
		CHECK(url.GetPort() == 0);
		CHECK(url.GetDomain() == "test.ru");
		CHECK(url.GetDocument() == "/path/to/document/");
	}
	SECTION("invalid parameters")
	{
		REQUIRE_THROWS_AS(HttpUrl("test.ru", "", Protocol::HTTP, 8080), std::invalid_argument);
		REQUIRE_THROWS_AS(HttpUrl("", "path", Protocol::HTTP, 200), std::invalid_argument);
		REQUIRE_THROWS_AS(HttpUrl("", "", Protocol::HTTP, 200), std::invalid_argument);
	}
}
