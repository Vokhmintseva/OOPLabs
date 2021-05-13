#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include <iostream>
#include <string>
#include "../BodiesLib/Body.h"
#include "../BodiesLib/Compound.h"
#include "../BodiesLib/Cone.h"
#include "../BodiesLib/Cylinder.h"
#include "../BodiesLib/Parallelepiped.h"
#include "../BodiesLib/Sphere.h"
#include "../BodiesLib/WorkSpace.h"

SCENARIO("bodies creation and getting parameters") {

    GIVEN("bodies") {

        Sphere sphere(22.54, 1.57);
        Cylinder cylinder(18.47, 0.69, 10.87);
        Cone cone(25.39, 2.09, 2.57);
        Parallelepiped parallelepiped(77.85, 26.87, 1.59, 2.47);
        Compound compound;

        THEN("getting sphere parameters") {
            CHECK(sphere.GetName() == "Sphere");
            CHECK(sphere.GetDensity() == 22.54);
            CHECK(sphere.GetRadius() == 1.57);
            CHECK(sphere.GetVolume() == Approx(16.21).margin(0.01));
            CHECK(sphere.GetMass() == Approx(365.38).margin(0.01));
            CHECK(sphere.ToString(0) == "Sphere\nDensity: 22.54\nVolume: 16.21\nMass: 365.38\nRadius: 1.57\n");
        }

        AND_THEN("getting cylinder parameters") {
            CHECK(cylinder.GetName() == "Cylinder");
            CHECK(cylinder.GetDensity() == 18.47);
            CHECK(cylinder.GetBaseRadius() == 0.69);
            CHECK(cylinder.GetHeight() == 10.87);
            CHECK(cylinder.GetVolume() == Approx(16.26).margin(0.01));
            CHECK(cylinder.GetMass() == Approx(300.29).margin(0.01));
            CHECK(cylinder.ToString(0) == "Cylinder\nDensity: 18.47\nVolume: 16.26\nMass: 300.29\nHeight: 10.87\nBaseRadius: 0.69\n");
        }

        AND_THEN("getting cone parameters") {
            CHECK(cone.GetName() == "Cone");
            CHECK(cone.GetDensity() == 25.39);
            CHECK(cone.GetBaseRadius() == 2.09);
            CHECK(cone.GetHeight() == 2.57);
            CHECK(cone.GetVolume() == Approx(11.76).margin(0.01));
            CHECK(cone.GetMass() == Approx(298.48).margin(0.01));
            CHECK(cone.ToString(0) == "Cone\nDensity: 25.39\nVolume: 11.76\nMass: 298.48\nHeight: 2.57\nBaseRadius: 2.09\n");
        }

        AND_THEN("getting parallelepiped parameters") {
            CHECK(parallelepiped.GetName() == "Parallelepiped");
            CHECK(parallelepiped.GetDensity() == 77.85);
            CHECK(parallelepiped.GetWidth() == 26.87);
            CHECK(parallelepiped.GetHeight() == 1.59);
            CHECK(parallelepiped.GetDepth() == 2.47);
            CHECK(parallelepiped.GetVolume() == Approx(105.53).margin(0.01));
            CHECK(parallelepiped.GetMass() == Approx(8215.24).margin(0.01));
            CHECK(parallelepiped.ToString(0) == "Parallelepiped\nDensity: 77.85\nVolume: 105.53\nMass: 8215.24\nWidth: 26.87\nHeight: 1.59\nDepth: 2.47\n");
        }

        AND_THEN("getting compound parameters") {
            std::string part1 = "Compound\nDensity: 0.00\nVolume: 0.00\nMass: 0.00\n";
            std::string expected = part1.append("BEGIN_BODIES_IN_COMPOUND:\nEND_BODIES_IN_COMPOUND\n");
            CHECK(compound.GetName() == "Compound");
            CHECK(compound.GetDensity() == 0.0);
            CHECK(compound.GetVolume() == 0.0);
            CHECK(compound.GetMass() == 0.0);
            CHECK(compound.ToString(0) == expected);
        }

        WHEN("adding created bodies to compound") {
            auto compoundPtr = std::make_shared<Compound>(compound);
            auto spherePtr = std::make_shared<Sphere>(sphere);
            auto cylinderPtr = std::make_shared<Cylinder>(cylinder);
            compoundPtr->AddChildBody(spherePtr);
            compoundPtr->AddChildBody(cylinderPtr);
            
            THEN("getting compound body parameters after child bodies were added") {
                std::string totalInfo = "Compound\nDensity: 20.50\nVolume: 32.47\nMass: 665.67\nBEGIN_BODIES_IN_COMPOUND:\n  Cylinder\n  Density: 18.47\n  Volume: 16.26\n  Mass: 300.29\n  Height: 10.87\n  BaseRadius: 0.69\n\n  Sphere\n  Density: 22.54\n  Volume: 16.21\n  Mass: 365.38\n  Radius: 1.57\n\nEND_BODIES_IN_COMPOUND\n";
                CHECK(compoundPtr->GetDensity() == Approx(20.50).margin(0.01));
                CHECK(compoundPtr->GetVolume() == Approx(32.47).margin(0.01));
                CHECK(compoundPtr->GetMass() == Approx(665.67).margin(0.01));
            }
            AND_WHEN("adding compound to compound") {
                auto parallelepipedPtr = std::make_shared<Parallelepiped>(parallelepiped);
                auto conePtr = std::make_shared<Cone>(cone);
                Compound compound2;
                auto compound2Ptr = std::make_shared<Compound>(compound2);
                compound2Ptr->AddChildBody(parallelepipedPtr);
                compound2Ptr->AddChildBody(conePtr);
                compoundPtr->AddChildBody(compound2Ptr);
               
                THEN("getting compound body parameters after child bodies were added including compound containing bodies") {
                    CHECK(compoundPtr->GetDensity() == Approx(61.29).margin(0.01));
                    CHECK(compoundPtr->GetVolume() == Approx(149.76).margin(0.01));
                    CHECK(compoundPtr->GetMass() == Approx(9179.39).margin(0.01));
                }
                AND_WHEN("adding compound to the same compound directly and indirectly") {
                    Compound compound3;
                    auto compound3Ptr = std::make_shared<Compound>(compound3);
                    compound2Ptr->AddChildBody(compound3Ptr);

                    THEN("'adding compound to the same compound' method returns false") {
                        CHECK(compoundPtr->AddChildBody(compoundPtr) == false);
                        CHECK(compound2Ptr->AddChildBody(compoundPtr) == false);
                        CHECK(compound3Ptr->AddChildBody(compoundPtr) == false);
                    }
                }
            }
        }
    }
}

TEST_CASE("Wrong arguments for cone given")
{
    std::string input = "cone 5 10 20 40\ncone 0 10 20\ncone 5 0 20\ncone 5 10 0\ncone -5 10 20\ncone 5 10";
    std::istringstream in(input);
    std::ostringstream out;
    WorkSpace workSpace(in, out);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
}

TEST_CASE("Wrong arguments for cylinder given")
{
    std::string input = "cylinder 5 10 20 40\ncylinder 0 10 20\ncylinder 5 0 20\ncylinder 5 10 0\ncylinder -5 10 20\ncylinder 5 10\n";
    std::istringstream in(input);
    std::ostringstream out;
    WorkSpace workSpace(in, out);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
}

TEST_CASE("Wrong arguments for sphere given")
{
    std::string input = "sphere 5 10 20\nsphere 0 10\nsphere 5 0\nsphere -5 10\nsphere 5 10 20\n";
    std::istringstream in(input);
    std::ostringstream out;
    WorkSpace workSpace(in, out);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
}

TEST_CASE("Wrong arguments for parallelepiped given")
{
    std::string input = "parallelepiped 5 10 20 40 50\nparallelepiped 0 10 20 30\nparallelepiped 5 0 20 30\nparallelepiped 5 10 0 30\nparallelepiped -5 10 20 30\nparallelepiped 5 10 20 40 50 60\n";
    std::istringstream in(input);
    std::ostringstream out;
    WorkSpace workSpace(in, out);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
    CHECK(workSpace.HandleCommand() == false);
}

TEST_CASE("check parallelepiped")
{
    Parallelepiped parallelepiped1(997, 10, 10, 10);
    Parallelepiped parallelepiped2(1.2754, 100, 100, 100);
    std::string input = "parallelepiped 997 10 10 10\nparallelepiped 1.2754 100 100 100\n";
    std::string info = "Parallelepiped\nDensity: 1.28\nVolume: 1000000.00\nMass: 1275400.00\nWidth: 100.00\nHeight: 100.00\nDepth: 100.00\n\nParallelepiped\nDensity: 997.00\nVolume: 1000.00\nMass: 997000.00\nWidth: 10.00\nHeight: 10.00\nDepth: 10.00\n\n";
    std::string maxMass = "THE BODY WITH THE BIGGEST MASS IS:\nParallelepiped\nDensity: 1.28\nVolume: 1000000.00\nMass: 1275400.00\nWidth: 100.00\nHeight: 100.00\nDepth: 100.00\n";
    std::string maxWeight = "THE BODY WITH THE LEAST WEIGHT IN WATER IS:\nParallelepiped\nDensity: 1.28\nVolume: 1000000.00\nMass: 1275400.00\nWidth: 100.00\nHeight: 100.00\nDepth: 100.00\n";
    std::string expectedOutput = info + maxMass + maxWeight;
    std::istringstream in(input);
    std::ostringstream out;
    WorkSpace workSpace(in, out);
    workSpace.HandleCommand();
    workSpace.HandleCommand();
    workSpace.PrintBodiesInfo();
    workSpace.PrintMaxMassBody();
    workSpace.PrintBodyWithLeastWeightInWater();
    CHECK(out.str() == expectedOutput);
}