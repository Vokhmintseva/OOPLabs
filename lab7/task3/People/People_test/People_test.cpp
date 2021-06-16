// People_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../People/People.h"
#include "../../../../../catch.hpp"

TEST_CASE("pupil")
{
	CPupil pupil("some lastname", "some name", "some middlename", "some address", "any school num", "any grade num");
	CHECK(pupil.GetLastname() == "some lastname");
	CHECK(pupil.GetName() == "some name");
	CHECK(pupil.GetMiddlename() == "some middlename");
	CHECK(pupil.GetAddress() == "some address");
	CHECK(pupil.GetSchool() == "any school num");
	CHECK(pupil.GetGrade() == "any grade num");
}