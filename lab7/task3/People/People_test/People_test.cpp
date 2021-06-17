#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../People/People.h"
#include "../../../../catch.hpp"

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

TEST_CASE("teacher")
{
	CTeacher teacher("some lastname", "some name", "some middlename", "some address", "any school subject");
	CHECK(teacher.GetLastname() == "some lastname");
	CHECK(teacher.GetName() == "some name");
	CHECK(teacher.GetMiddlename() == "some middlename");
	CHECK(teacher.GetAddress() == "some address");
	CHECK(teacher.GetSubject() == "any school subject");
}

TEST_CASE("worker")
{
	CWorker worker("some lastname", "some name", "some middlename", "some address", "any speciality");
	CHECK(worker.GetLastname() == "some lastname");
	CHECK(worker.GetName() == "some name");
	CHECK(worker.GetMiddlename() == "some middlename");
	CHECK(worker.GetAddress() == "some address");
	CHECK(worker.GetSpeciality() == "any speciality");
}

TEST_CASE("student")
{
	CStudent student("some lastname", "some name", "some middlename", "some address", "some university", "any student card num");
	CHECK(student.GetLastname() == "some lastname");
	CHECK(student.GetName() == "some name");
	CHECK(student.GetMiddlename() == "some middlename");
	CHECK(student.GetAddress() == "some address");
	CHECK(student.GetUniversity() == "some university");
	CHECK(student.GetStudentCard() == "any student card num");
}

TEST_CASE("advanced student")
{
	CAdvancedStudent advancedStudent("some lastname", "some name", "some middlename", "some address", "some university", "any student card num", "some thesis");
	CHECK(advancedStudent.GetLastname() == "some lastname");
	CHECK(advancedStudent.GetName() == "some name");
	CHECK(advancedStudent.GetMiddlename() == "some middlename");
	CHECK(advancedStudent.GetAddress() == "some address");
	CHECK(advancedStudent.GetUniversity() == "some university");
	CHECK(advancedStudent.GetStudentCard() == "any student card num");
	CHECK(advancedStudent.GetThesis() == "some thesis");
}