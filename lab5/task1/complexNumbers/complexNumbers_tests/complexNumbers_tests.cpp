// complexNumbers_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include <iostream>
#include <string>
#include "../complexNumbers/Complex.h"

TEST_CASE("Complex number getting magnitude and argument test")
{
	SECTION("0 real and image parts")
	{
		Complex complex;
		CHECK(complex.Re() == 0.0);
		CHECK(complex.Im() == 0.0);
		CHECK(complex.GetMagnitude() == 0.0);
		double arg = complex.GetArgument();
		CHECK(arg != arg);
		Complex res = complex + Complex(1, 2);
		CHECK(res.Re() == 1);
		CHECK(res.Im() == 2);
	}

	SECTION("0 real and negative image parts")
	{
		Complex complex(0, -2);
		CHECK(complex.Re() == 0.0);
		CHECK(complex.Im() == -2);
		CHECK(complex.GetMagnitude() == 2.0);
		double arg = complex.GetArgument();
		CHECK(arg != arg);
		Complex res = complex + Complex(1, 2);
		CHECK(res.Re() == 1);
		CHECK(res.Im() == 0);
	}

	SECTION("negative real and image parts")
	{
		Complex complex(-3, -2);
		CHECK(complex.Re() == -3);
		CHECK(complex.Im() == -2);
		CHECK(complex.GetMagnitude() == Approx(3.61).margin(0.01));
		CHECK(complex.GetArgument() == Approx(-2.55).margin(0.01));
		Complex res = complex + Complex(1, 2);
		CHECK(res.Re() == -2);
		CHECK(res.Im() == 0);
	}

	SECTION("negative real and positive image parts")
	{
		Complex complex(-5, 4);
		CHECK(complex.Re() == -5);
		CHECK(complex.Im() == 4);
		CHECK(complex.GetMagnitude() == Approx(6.41).margin(0.01));
		CHECK(complex.GetArgument() == Approx(2.47).margin(0.01));
		Complex res1 = complex + Complex(1, 2);
		CHECK(res1.Re() == -4);
		CHECK(res1.Im() == 6);
	}

	SECTION("positive real and negative image parts")
	{
		Complex complex(7, -4);
		CHECK(complex.Re() == 7);
		CHECK(complex.Im() == -4);
		CHECK(complex.GetMagnitude() == Approx(8.06).margin(0.01));
		CHECK(complex.GetArgument() == Approx(-0.52).margin(0.01));
		Complex res1 = complex + Complex(1, 2);
		CHECK(res1.Re() == 8);
		CHECK(res1.Im() == -2);
	}
	
	SECTION("positive real and image parts")
	{
		Complex complex(7, 9);
		CHECK(complex.Re() == 7);
		CHECK(complex.Im() == 9);
		CHECK(complex.GetMagnitude() == Approx(11.40).margin(0.01));
		CHECK(complex.GetArgument() == Approx(0.91).margin(0.01));
	}
}

TEST_CASE("Binary +")
{
	Complex res1 = Complex(7, 9) + 1.15;
	CHECK(res1.Re() == 8.15);
	CHECK(res1.Im() == 9);

	Complex res2 = Complex(-4, -2) + Complex(11.5, 16.4);
	CHECK(res2.Re() == 7.5);
	CHECK(res2.Im() == Approx(14.4).margin(0.01));
}

TEST_CASE("Binary -")
{
	Complex res1 = Complex(7, 9) - 1.15;
	CHECK(res1.Re() == 5.85);
	CHECK(res1.Im() == 9);

	Complex res2 = Complex(-4, -2) - Complex(11.5, 16.4);
	CHECK(res2.Re() == -15.5);
	CHECK(res2.Im() == Approx(-18.4).margin(0.01));

	Complex res3 = 11 - Complex(8, 17);
	CHECK(res3.Re() == 3);
	CHECK(res3.Im() == -17);
}

TEST_CASE("Binary *")
{
	Complex res1 = Complex(7, 9) * 1.15;
	CHECK(res1.Re() == Approx(8.05).margin(0.01));
	CHECK(res1.Im() == Approx(10.35).margin(0.01));
	
	Complex res2 = Complex(2, 1) * Complex(3, 4);
	CHECK(res2.Re() == 2);
	CHECK(res2.Im() == 11);

	Complex res3 = 11 * Complex(8, 17);
	CHECK(res3.Re() == Approx(88));
	CHECK(res3.Im() == Approx(187));
}
