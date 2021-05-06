#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include <iostream>
#include <string>
#include "../BodiesLib/Body.h"
#include "../BodiesLib/BodyNameResolver.h"
#include "../BodiesLib/Compound.h"
#include "../BodiesLib/Cone.h"
#include "../BodiesLib/Cylinder.h"
#include "../BodiesLib/Parallelepiped.h"
#include "../BodiesLib/Sphere.h"
#include "../BodiesLib/WorkSpace.h"

TEST_CASE("Sphere")
{
	Sphere sphere(22.54, 32.47);
	SECTION("check sphere getting parameters")
	{
		CHECK(sphere.GetName() == "Sphere");
		CHECK(sphere.GetDensity() == 22.54);
		CHECK(sphere.GetVolume() == 32.47);
		CHECK(sphere.GetMass() == Approx(731.87).margin(0.01));
		CHECK(sphere.GetRadius() == Approx(1.57).margin(0.01));
		CHECK(sphere.ToString() == "Sphere\nDensity: 22.54\nVolume: 32.47\nMass: 731.87\nRadius: 1.57\n");
		CHECK(BodyNameResolver::ResolveName(sphere.GetType()) == "Sphere");
	}
}

TEST_CASE("Cylinder")
{
	Cylinder cylinder(18.47, 16.29, 10.87);
	SECTION("check cylinder getting parameters")
	{
		CHECK(cylinder.GetName() == "Cylinder");
		CHECK(cylinder.GetDensity() == 18.47);
		CHECK(cylinder.GetVolume() == 16.29);
		CHECK(cylinder.GetMass() == Approx(300.88).margin(0.01));
		CHECK(cylinder.GetHeight() == 10.87);
		CHECK(cylinder.GetBaseRadius() == Approx(0.69).margin(0.01));
		CHECK(cylinder.ToString() == "Cylinder\nDensity: 18.47\nVolume: 16.29\nMass: 300.88\nHeight: 10.87\nBaseRadius: 0.69\n");
		CHECK(BodyNameResolver::ResolveName(cylinder.GetType()) == "Cylinder");
	}
}

TEST_CASE("Cone")
{
	Cone cone(25.39, 11.79, 2.57);
	SECTION("check cone getting parameters")
	{
		CHECK(cone.GetName() == "Cone");
		CHECK(cone.GetDensity() == 25.39);
		CHECK(cone.GetVolume() == 11.79);
		CHECK(cone.GetMass() == Approx(299.35).margin(0.01));
		CHECK(cone.GetHeight() == 2.57);
		CHECK(cone.GetBaseRadius() == Approx(2.09).margin(0.01));
		CHECK(cone.ToString() == "Cone\nDensity: 25.39\nVolume: 11.79\nMass: 299.35\nHeight: 2.57\nBaseRadius: 2.09\n");
		CHECK(BodyNameResolver::ResolveName(cone.GetType()) == "Cone");
	}
}

TEST_CASE("Parallelepiped")
{
	Parallelepiped parallelepiped(77.85, 105.49, 26.87, 1.59);
	SECTION("check parallelepiped getting parameters")
	{
		CHECK(parallelepiped.GetName() == "Parallelepiped");
		CHECK(parallelepiped.GetDensity() == 77.85);
		CHECK(parallelepiped.GetVolume() == 105.49);
		CHECK(parallelepiped.GetMass() == Approx(8212.40).margin(0.01));
		CHECK(parallelepiped.GetWidth() == 26.87);
		CHECK(parallelepiped.GetHeight() == 1.59);
		CHECK(parallelepiped.GetDepth() == Approx(2.47).margin(0.01));
		CHECK(parallelepiped.ToString() == "Parallelepiped\nDensity: 77.85\nVolume: 105.49\nMass: 8212.40\nWidth: 26.87\nHeight: 1.59\nDepth: 2.47\n");
		CHECK(BodyNameResolver::ResolveName(parallelepiped.GetType()) == "Parallelepiped");
	}
}

TEST_CASE("Compound")
{
	Compound compound;
	SECTION("check compound getting parameters")
	{
		std::string part1 = "Compound\nDensity: 0.00\nVolume: 0.00\nMass: 0.00\n\n";
		std::string expected = part1.append("BEGIN_BODIES_IN_COMPOUND:\n\nEND_BODIES_IN_COMPOUND\n");
		CHECK(compound.GetName() == "Compound");
		CHECK(compound.GetDensity() == 0.0);
		CHECK(compound.GetVolume() == 0.0);
		CHECK(compound.GetMass() == 0.0);
		CHECK(compound.ToString() == expected);
		CHECK(BodyNameResolver::ResolveName(compound.GetType()) == "Compound");
	}
}

SCENARIO("bodies creation and getting parameters") {

    GIVEN("bodies") {

        Sphere sphere(22.54, 32.47);
        Cylinder cylinder(18.47, 16.29, 10.87);
        Cone cone(25.39, 11.79, 2.57);
        Parallelepiped parallelepiped(77.85, 105.49, 26.87, 1.59);
        Compound compound;

        THEN("getting sphere parameters") {
            CHECK(sphere.GetName() == "Sphere");
            CHECK(sphere.GetDensity() == 22.54);
            CHECK(sphere.GetVolume() == 32.47);
            CHECK(sphere.GetMass() == Approx(731.87).margin(0.01));
            CHECK(sphere.GetRadius() == Approx(1.57).margin(0.01));
            CHECK(sphere.ToString() == "Sphere\nDensity: 22.54\nVolume: 32.47\nMass: 731.87\nRadius: 1.57\n");
            CHECK(BodyNameResolver::ResolveName(sphere.GetType()) == "Sphere");
        }

        AND_THEN("getting cylinder parameters") {
            CHECK(cylinder.GetName() == "Cylinder");
            CHECK(cylinder.GetDensity() == 18.47);
            CHECK(cylinder.GetVolume() == 16.29);
            CHECK(cylinder.GetMass() == Approx(300.88).margin(0.01));
            CHECK(cylinder.GetHeight() == 10.87);
            CHECK(cylinder.GetBaseRadius() == Approx(0.69).margin(0.01));
            CHECK(cylinder.ToString() == "Cylinder\nDensity: 18.47\nVolume: 16.29\nMass: 300.88\nHeight: 10.87\nBaseRadius: 0.69\n");
            CHECK(BodyNameResolver::ResolveName(cylinder.GetType()) == "Cylinder");
        }

        AND_THEN("getting cone parameters") {
            CHECK(cone.GetName() == "Cone");
            CHECK(cone.GetDensity() == 25.39);
            CHECK(cone.GetVolume() == 11.79);
            CHECK(cone.GetMass() == Approx(299.35).margin(0.01));
            CHECK(cone.GetHeight() == 2.57);
            CHECK(cone.GetBaseRadius() == Approx(2.09).margin(0.01));
            CHECK(cone.ToString() == "Cone\nDensity: 25.39\nVolume: 11.79\nMass: 299.35\nHeight: 2.57\nBaseRadius: 2.09\n");
            CHECK(BodyNameResolver::ResolveName(cone.GetType()) == "Cone");
        }

        AND_THEN("getting parallelepiped parameters") {
            CHECK(parallelepiped.GetName() == "Parallelepiped");
            CHECK(parallelepiped.GetDensity() == 77.85);
            CHECK(parallelepiped.GetVolume() == 105.49);
            CHECK(parallelepiped.GetMass() == Approx(8212.40).margin(0.01));
            CHECK(parallelepiped.GetWidth() == 26.87);
            CHECK(parallelepiped.GetHeight() == 1.59);
            CHECK(parallelepiped.GetDepth() == Approx(2.47).margin(0.01));
            CHECK(parallelepiped.ToString() == "Parallelepiped\nDensity: 77.85\nVolume: 105.49\nMass: 8212.40\nWidth: 26.87\nHeight: 1.59\nDepth: 2.47\n");
            CHECK(BodyNameResolver::ResolveName(parallelepiped.GetType()) == "Parallelepiped");
        }

        AND_THEN("getting compound parameters") {
            std::string part1 = "Compound\nDensity: 0.00\nVolume: 0.00\nMass: 0.00\n\n";
            std::string expected = part1.append("BEGIN_BODIES_IN_COMPOUND:\n\nEND_BODIES_IN_COMPOUND\n");
            CHECK(compound.GetName() == "Compound");
            CHECK(compound.GetDensity() == 0.0);
            CHECK(compound.GetVolume() == 0.0);
            CHECK(compound.GetMass() == 0.0);
            CHECK(compound.ToString() == expected);
            CHECK(BodyNameResolver::ResolveName(compound.GetType()) == "Compound");
        }

        WHEN("adding created bodies to compound") {
            auto spherePtr = std::make_shared<Sphere>(sphere);
            auto cylinderPtr = std::make_shared<Cylinder>(cylinder);
            compound.AddChildBody(spherePtr);
            compound.AddChildBody(cylinderPtr);
            
            THEN("getting compound body parameters after child bodies were added") {
                std::string compoundInfoBegin = "Compound\nDensity: 21.18\nVolume: 48.76\nMass: 1032.75\n\nBEGIN_BODIES_IN_COMPOUND:\n\n";
                std::string cylinderInfo = "Cylinder\nDensity: 18.47\nVolume: 16.29\nMass: 300.88\nHeight: 10.87\nBaseRadius: 0.69\n\n";
                std::string sphereInfo = "Sphere\nDensity: 22.54\nVolume: 32.47\nMass: 731.87\nRadius: 1.57\n\n";
                std::string compoundInfoEnd = "END_BODIES_IN_COMPOUND\n";
                std::string totalInfo = compoundInfoBegin + cylinderInfo + sphereInfo + compoundInfoEnd;
                CHECK(compound.GetDensity() == Approx(21.18).margin(0.01));
                CHECK(compound.GetVolume() == Approx(48.76).margin(0.01));
                CHECK(compound.GetMass() == Approx(1032.75).margin(0.01));
                CHECK(compound.ToString() == totalInfo);
            }
            AND_WHEN("adding compound to compound") {
                auto parallelepipedPtr = std::make_shared<Parallelepiped>(parallelepiped);
                auto conePtr = std::make_shared<Cone>(cone);
                Compound compound2;
                auto compound2Ptr = std::make_shared<Compound>(compound2);
                compound.AddChildBody(compound2Ptr);
                compound2Ptr->AddChildBody(parallelepipedPtr);
                compound2Ptr->AddChildBody(conePtr);
                
                THEN("getting compound body parameters after child bodies were added including compound containing bodies") {
                    std::string part1 = "Compound\nDensity: 57.48\nVolume: 166.04\nMass: 9544.49\n\nBEGIN_BODIES_IN_COMPOUND:\n\n";
                    std::string part2 = "Compound\nDensity: 72.58\nVolume: 117.28\nMass: 8511.74\n\nBEGIN_BODIES_IN_COMPOUND:\n\n";
                    std::string part3 = "Cone\nDensity: 25.39\nVolume: 11.79\nMass: 299.35\nHeight: 2.57\nBaseRadius: 2.09\n\n";
                    std::string part4 = "Parallelepiped\nDensity: 77.85\nVolume: 105.49\nMass: 8212.40\nWidth: 26.87\nHeight: 1.59\nDepth: 2.47\n\nEND_BODIES_IN_COMPOUND\n\n";
                    std::string part5 = "Cylinder\nDensity: 18.47\nVolume: 16.29\nMass: 300.88\nHeight: 10.87\nBaseRadius: 0.69\n\n";
                    std::string part6 = "Sphere\nDensity: 22.54\nVolume: 32.47\nMass: 731.87\nRadius: 1.57\n\nEND_BODIES_IN_COMPOUND\n";
                    std::string totalInfo = part1 + part2 + part3 + part4 + part5 + part6;
                    CHECK(compound.GetDensity() == Approx(57.48).margin(0.01));
                    CHECK(compound.GetVolume() == Approx(166.04).margin(0.01));
                    CHECK(compound.GetMass() == Approx(9544.49).margin(0.01));
                    CHECK(compound.ToString() == totalInfo);
                }
            }
        }
    }
}