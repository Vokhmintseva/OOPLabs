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
	CHECK(res3.Re() == 88);
	CHECK(res3.Im() == 187);

	Complex res4 = Complex(-8.46, 13.25) * Complex(-5.4, 2.7);
	CHECK(res4.Re() == Approx(9.91).margin(0.01));
	CHECK(res4.Im() == Approx(-94.39).margin(0.01));
}

TEST_CASE("Binary /")
{
	Complex res1 = Complex(3, 4) / Complex(2, 1);
	CHECK(res1.Re() == 2);
	CHECK(res1.Im() == 1);

	Complex res2 = Complex(23, 1) / Complex(3, 1);
	CHECK(res2.Re() == 7);
	CHECK(res2.Im() == -2);

	Complex res3 = Complex(-2, 1) / Complex(1, -1);
	CHECK(res3.Re() == -1.5);
	CHECK(res3.Im() == -0.5);

	Complex res4 = Complex(3, 4) / Complex(5, -6);
	CHECK(res4.Re() == Approx(-0.15).margin(0.01));
	CHECK(res4.Im() == Approx(0.62).margin(0.01));

	Complex res5 = Complex(-7, 4) / 3;
	CHECK(res5.Re() == Approx(-2.33).margin(0.01));
	CHECK(res5.Im() == Approx(1.33).margin(0.01));

	Complex res6 = Complex(0, 0) / Complex(5, -6);
	CHECK(res6.Re() == 0);
	CHECK(res6.Im() == 0);

	Complex res7 = 0 / Complex(5, -6);
	CHECK(res7.Re() == 0);
	CHECK(res7.Im() == 0);

	Complex res8 = 5 / Complex(5, -6);
	CHECK(res8.Re() == Approx(0.41).margin(0.01));
	CHECK(res8.Im() == Approx(0.49).margin(0.01));

	REQUIRE_THROWS_AS(Complex(3, 4) / 0, std::invalid_argument);
	REQUIRE_THROWS_AS(Complex(3, 4) / Complex(0, 0), std::invalid_argument);
}

TEST_CASE("Unary +")
{
	Complex res1 = +Complex(7, 9);
	CHECK(res1.Re() == 7);
	CHECK(res1.Im() == 9);
}

TEST_CASE("Operator -")
{
	Complex res1 = -Complex(-5, 2);
	CHECK(res1.Re() == 5);
	CHECK(res1.Im() == -2);
}

TEST_CASE("Operator +=")
{
	Complex res1(5.6, 7.9);
	res1 += Complex(-5, 2);
	CHECK(res1.Re() == Approx(0.6).margin(0.01));
	CHECK(res1.Im() == 9.9);

	Complex res2(5.6, 7.9);
	res2 += 8.7;
	CHECK(res2.Re() == Approx(14.3).margin(0.01));
	CHECK(res2.Im() == Approx(7.9).margin(0.01));

	Complex res3;
	res3 += -9.4;
	CHECK(res3.Re() == Approx(-9.4).margin(0.01));
	CHECK(res3.Im() == 0);
}

TEST_CASE("Operator *=")
{
	Complex res1(-8.46, 13.25);
	res1 *= Complex(-5.4, 2.7);
	CHECK(res1.Re() == Approx(9.91).margin(0.01));
	CHECK(res1.Im() == Approx(-94.39).margin(0.01));

	Complex res2(15.46, -11.81);
	res2 *= 4.25;
	CHECK(res2.Re() == Approx(65.71).margin(0.01));
	CHECK(res2.Im() == Approx(-50.19).margin(0.01));
}

TEST_CASE("Operator /=")
{
	Complex res1(11.78, 16.45);
	res1 /= Complex(-9.41, 0.87);
	CHECK(res1.Re() == Approx(-1.08).margin(0.01));
	CHECK(res1.Im() == Approx(-1.85).margin(0.01));

	Complex res2(19.87, -1.40);
	res2 /= -5.95;
	CHECK(res2.Re() == Approx(-3.34).margin(0.01));
	CHECK(res2.Im() == Approx(0.24).margin(0.01));

	REQUIRE_THROWS_AS(res1 /= 0, std::invalid_argument);
	REQUIRE_THROWS_AS(res1 /= Complex(0, 0), std::invalid_argument);
}

TEST_CASE("Operator ==")
{
	Complex op1(19.45, -11.21);
	CHECK((op1 == Complex(19.45, -11.21)) == true);
	CHECK((op1 == Complex(19.46, -11.20)) == false);
	CHECK((op1 == Complex(19.45, -11.20)) == false);
	CHECK((op1 == Complex(19.46, -11.21)) == false);
	CHECK((19.45 == op1) == false);

	Complex op2(15.45);
	CHECK((op2 == 15.45) == true);
	CHECK((op2 == Complex(15.45, 0)) == true);

	Complex op3(15.72);
	CHECK((15.72 == op3) == true);

	Complex op4(15.72, 0.01);
	CHECK((15.72 == op4) == false);

	Complex op5(0.00000000001, -0.00000000001);
	CHECK((op5 == Complex(0.00000000002, -0.00000000002)) == false);
}

TEST_CASE("Operator !=")
{
	Complex op1(19.45, -11.21);
	CHECK((op1 != Complex(19.45, -11.21)) == false);
	CHECK((op1 != Complex(19.46, -11.20)) == true);
	CHECK((op1 != Complex(19.45, -11.20)) == true);
	CHECK((op1 != Complex(19.46, -11.21)) == true);
	CHECK((19.45 != op1) == true);

	Complex op2(15.45);
	CHECK((op2 != 15.45) == false);
	CHECK((op2 != Complex(15.45, 0)) == false);

	Complex op3(15.72);
	CHECK((15.72 != op3) == false);

	Complex op4(15.72, 0.01);
	CHECK((15.72 != op4) == true);

	Complex op5(0.00000000001, -0.00000000001);
	CHECK((op5 != Complex(0.00000000002, -0.00000000002)) == true);
}


TEST_CASE("Operator <<")
{
	Complex complex1(19, 11.21);
	std::ostringstream output;
	output << complex1;
	CHECK(output.str() == "19+11.2i");

	output.str("");
	Complex complex2(0.04, -11.05);
	output << complex2;
	CHECK(output.str() == "0-11.1i");

	output.str("");
	Complex complex3(0.05, -0.04);
	output << complex3;
	CHECK(output.str() == "0.1-0i");

	output.str("");
	Complex complex4(-0.049, -0.049);
	output << complex4;
	CHECK(output.str() == "0-0i");

	output.str("");
	Complex complex5(14.4, -15.4);
	output << complex5;
	CHECK(output.str() == "14.4-15.4i");

	output.str("");
	Complex complex6(-0.05, 0.05);
	output << complex6;
	CHECK(output.str() == "-0.1+0.1i");

	output.str("");
	Complex complex7(5);
	output << complex7;
	CHECK(output.str() == "5+0i");

	output.str("");
	Complex complex8;
	output << complex8;
	CHECK(output.str() == "0+0i");
}

TEST_CASE("Operator >>")
{
	Complex complex1;
	std::istringstream input;
	input.str("2-4i");
	input >> complex1;
	CHECK(complex1.Re() == 2);
	CHECK(complex1.Im() == -4);

	Complex complex2;
	input.str("");
	input.str("2-4");
	input >> complex2;
	CHECK(input.fail() == true);

	Complex complex3;
	input.clear();
	input.str("2.56+4.27i");
	input >> complex3;
	CHECK(complex3.Re() == 2.56);
	CHECK(complex3.Im() == 4.27);

	Complex complex4;
	input.str("-0.009-4.559i");
	input >> complex4;
	CHECK(complex4.Re() == -0.009);
	CHECK(complex4.Im() == -4.559);

	Complex complex5;
	input.str("0-0i");
	input >> complex5;
	CHECK(complex5.Re() == 0);
	CHECK(complex5.Im() == 0);
}